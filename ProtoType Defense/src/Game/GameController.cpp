#include "GameController.h"

#include "ShaderManager.h"

#include <sstream>

using namespace glm;

static int numRounds = 5;

static int numTextures = 16;

GameController::GameController()
	: money(600), lives(100), speed(1), active(false), currentRound(nullptr), renderer(numTextures)
{
	for (int i = 0; i < numRounds; i++)
	{
		rounds.emplace_back(getPath());
	}
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

void GameController::startGame()
{
	std::cout << "Game Started: " << rounds.size() << " rounds" << std::endl;
	
	currentRound = &rounds.front();
	currentRound->startRound();
	std::cout << "Starting Round " << numRounds - rounds.size() + 1 << std::endl;

	active = true;
}

void GameController::endGame() const
{
	std::cout << "Game Ended. Lives left = " << lives << std::endl;
}

void GameController::nextRound()
{
	rounds.pop_front();
	
	if (!rounds.empty())
	{
		currentRound = &rounds.front();
		std::cout << "Starting Round " << numRounds - rounds.size() + 1 << std::endl;
		return;
	}
	std::cout << "All " << numRounds << " Rounds completed " << std::endl;
}

void GameController::sendEnemy() const
{
	currentRound->sendEnemy();
}

void GameController::fastForward(float speedPercent)
{
	speed *= speedPercent;
}

std::string GameController::getStatus() const
{
	std::stringstream ss;
	ss << "Lives: " << lives << " || Money: " << money << " || Round: " << (numRounds - rounds.size() + 1);
	std::string s = ss.str();
	return s;
}
