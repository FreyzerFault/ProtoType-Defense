#include "GameController.h"

#include "ShaderManager.h"

#include <sstream>

using namespace glm;

static int numRounds = 5;

static int numTextures = 16;

GameController::GameController()
	: money(600), lives(100), speed(1), active(false), renderer(numTextures)
{
	for (int i = 0; i < numRounds; i++)
	{
		int reward = 100;
		rounds.emplace_back(i+1, reward);
		roundStack.push_back(&rounds.back());
	}
	currentRound = *roundStack.front();
}

void GameController::update(float deltaTime)
{
	deltaTime *= speed;
	
	getPath().moveEnemies(deltaTime);
	
	if (!roundStack.empty())
	{
		if (currentRound.isEnded())
		{
			if (getPath().noEnemiesLeft())
				nextRound();
		}
		else
			currentRound.sendEnemy(deltaTime);
	}
	else
		if (getPath().noEnemiesLeft())
			endGame(); // End when the Enemies from last Round disapear;
}

void GameController::render(mat4 mvp)
{
	// Scene MVP
	renderer.setMVP(mvp);

	// TILEMAP
	

	// TOWERS
	for (const Platform& platform : platforms)
	{
		Tower& tower = platform.getTower();
		renderer.draw(tower.getSprite());

		// PROJECTILES
		for (Projectile& projectile : tower.getProjectiles())
		{
			renderer.draw(projectile.getSprite());
			renderer.draw(projectile.getHitbox());
		}
	}

	// ENEMIES
	const std::list<Enemy>& enemyList = getPath().getEnemyList();
	for (const Enemy& enemy : enemyList)
	{
		renderer.draw(enemy.getSprite());
		renderer.draw(enemy.getHitbox());
	}
}


void GameController::reset()
{
	getPath().removeEnemies();
	
	roundStack.clear();
	for (Round& round: rounds)
	{
		roundStack.push_back(&round);
	}
	startGame();
}



void GameController::startGame()
{
	std::cout << "Game Started: " << roundStack.size() << " rounds" << std::endl;
	
	currentRound = *roundStack.front();
	currentRound.startRound(getPath());

	active = true;
}

void GameController::endGame()
{
	std::cout << "Game Ended. Lives left = " << lives << std::endl;
	active = false;
}

void GameController::nextRound()
{
	money += currentRound.getReward();
	roundStack.pop_front();
	
	if (!roundStack.empty())
	{
		currentRound = *roundStack.front();
		currentRound.startRound(getPath());
	}
}

void GameController::fastForward(float speedPercent)
{
	speed *= speedPercent / 100;
}

std::string GameController::getStatus() const
{
	std::stringstream ss;
	ss << "Lives: " << lives << " || Money: " << money << " || Round: " << (numRounds - rounds.size() + 1);
	std::string s = ss.str();
	return s;
}
