#include "pch.h"
#include "GameController.h"

#include "Objects/Projectile.h"

using namespace glm;

static int numRounds = 5;
static int numTextures = 3;

static int startingLives = 100;
static int startingMoney = 2000;

static float maxGameSpeed = 20;
static float minGameSpeed = 0.01;

GameController::GameController()
	: money(startingMoney), lives(startingLives), speed(1), active(false), map(vec2(10,10), &renderer), renderer(numTextures)
{
	for (int i = 0; i < numRounds; i++)
	{
		int reward = 100;
		rounds.emplace_back(i+1, reward);
		roundStack.push_back(&rounds.back());
	}
	currentRound = *roundStack.front();

	audioManager.addSong("Blue Sphere Stage (8-BIT) - Sonic Mania");
	audioManager.addSong("Donkey Kong Country Theme Restored to HD");
	audioManager.addSong("Hi-Spec Robo Go 8-bit - Sonic Mania [Hardboiled Heavies Theme] (0CC-Famitracker, 2A03)");
	audioManager.addSong("Nokia 3220 Ringtone - Espionage  (Audio Original)");
	audioManager.addSong("Sonic Mania - Stardust Speedway Act 1 8 Bit Remix");
	audioManager.addSong("Studiopolis Act 1 (8-BIT) - Sonic Mania");
}


void GameController::clearTower()
{
	for (Tower* tower : towers)
	{
		tower->sell();
	}
	towers.clear();
	selectedTower = nullptr;
}

void GameController::startGame()
{
	std::cout << "Game Started: " << roundStack.size() << " rounds" << std::endl;

	audioManager.playSong("Blue Sphere Stage (8-BIT) - Sonic Mania");

	currentRound = *roundStack.front();
	currentRound.startRound(getPath());

	active = true;
}

void GameController::update(float deltaTime)
{
	deltaTime *= speed;
	
	// TOWERS

	for (Tower* tower : towers)
	{
		// If a projectile collide with an Enemy: pierce-- & Enemy lose health
		std::list<Enemy*>& enemies = getPath().getEnemyList();
		auto itE = enemies.begin();
		while (itE != enemies.end())
		{
			Enemy* enemy = *itE;

			auto itP = tower->getProjectiles().begin();

			while (itP != tower->getProjectiles().end())
			{
				Projectile& projectile = *itP;

				if (projectile.impact(enemy->getHitbox()))
				{
					enemy->getHit(tower->getDmg());
					audioManager.playSound("pop");
				}
				else
					// Get a 0 damage hit to unmark enemy as hit, so flashy red color disappear
					enemy->getHit(0);

				// If projectile pierce is <= 0, it's removed
				if (projectile.getPierce() <= 0)
				{
					const auto itaux = itP;
					++itP;
					tower->getProjectiles().erase(itaux);
				}
				else
					++itP;
			}

			// If enemy is dead, it's removed from Path
			if (enemy->getLife() <= 0)
			{
				const auto it = itE;
				++itE;
				money += getPath().deleteEnemy(enemy);
				audioManager.playSound("coin");
			}
			else
				++itE;
		}


		// Towers aim enemies if exist
		if (!getPath().noEnemiesLeft())
			tower->aim(getPath());
		else
			tower->aim(nullptr);

		// Towers try to Shoot
		tower->shoot(deltaTime);

		// Projectiles move
		tower->moveProjectiles(deltaTime);
	}

	
	// ENEMIES
	moveEnemies(deltaTime);

	
	// ROUNDS
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
	
	if (firstFrame)
	{
		map.setupRendering(renderer);
		firstFrame = false;
	}

	// TILEMAP
	map.draw(renderer);

	// TOWERS
	map.drawTowerRange(renderer);
	map.drawTowers(renderer);

	// ENEMIES
	map.drawEnemies(renderer);

	// HITBOXES
	if (activeHitbox)
		map.drawHitboxes(renderer);
}


void GameController::reset()
{
	AudioManager::pauseMusic();
	
	// Clear Enemies
	getPath().clearEnemies();

	// Clear Towers
	clearTower();

	// Reset Player Resources
	lives = startingLives;
	money = startingMoney;

	// Reset rounds
	roundStack.clear();
	for (Round& round: rounds)
	{
		roundStack.push_back(&round);
	}
	startGame();
}

bool GameController::placeTower(glm::vec2 pos, TypeTower type)
{
	// If Tower there is already a Tower return true
	if (getTower(pos) != nullptr)
		return false;
	
	Platform* platform = map.getPlatform(pos);
	// If there's not platform don't place it
	if (platform == nullptr)
		return false;

	platform->placeTower(type);
	
	// Select it
	selectTower(pos);
	towers.push_back(selectedTower);

	money -= selectedTower->getCost();
	
	return true;
}

bool GameController::sellTower(glm::vec2 pos)
{
	Tower* tower = getTower(pos);
	
	// If no tower return false
	if (tower == nullptr) return false;

	// If selected deselect
	if (selectedTower == tower)
		selectedTower = nullptr;

	// Delete from the list
	for (auto it = towers.begin(); it != towers.end(); ++it)
		if (tower == *it)
		{
			towers.erase(it);
			break;
		}

	// Erase from the platform
	Platform* platform = tower->getPlatform();
	const int sellprice = platform->sellTower();

	// Update Money with the sell price
	money += sellprice;

	return true;
}

bool GameController::selectTower(glm::vec2 pos)
{
	deselectTower();
	
	selectedTower = getTower(pos);
	if (selectedTower != nullptr)
	{
		selectedTower->select();
		return true;
	}
	return false;
}

bool GameController::deselectTower()
{
	if (selectedTower == nullptr)
		return false;
	
	selectedTower->deselect();
	selectedTower = nullptr;
	
	return true;
}

Tower* GameController::getTower(glm::vec2 pos)
{
	Platform* pl = map.getPlatform(pos);
	if (pl != nullptr)
		return pl->getTower();
	return nullptr;
}


void GameController::moveEnemies(float deltaTime)
{
	lives -= getPath().moveEnemies(deltaTime);
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

void GameController::pauseGame()
{
	active = false;
	AudioManager::pauseMusic();
}

void GameController::resumeGame()
{
	active = true;
	AudioManager::resumeMusic();
}

void GameController::fastForward(float speedPercent)
{
	speed *= speedPercent / 100;
	
	// Limited to a Min-Max Speed
	if (speed >= maxGameSpeed) speed = maxGameSpeed;
	if (speed <= minGameSpeed) speed = minGameSpeed;
}

std::string GameController::getStatus() const
{
	std::stringstream ss;
	ss << "Lives: " << lives << " || Money: " << money << " || Round: " << (numRounds - rounds.size() + 1);
	std::string s = ss.str();
	return s;
}
