#pragma once
#include "pch.h"


#include "AudioManager.h"
#include "Objects/Tower.h"
#include "Objects/Enemy.h"

#include "Map/Platform.h"
#include "Map/Map.h"
#include "Map/Round.h"

#include "Renderer.h"

class GameController
{
public:
	GameController();

	// Pipeline
	void update(float deltaTime);
	void render(glm::mat4 mvp);
	void reset();

	// Map
	Path& getPath() { return map.getPath(); }
	Map& getMap() { return map; }

	// Towers
	bool placeTower(glm::vec2 pos, TypeTower type);
	bool sellTower(glm::vec2 pos);
	bool selectTower(glm::vec2 pos);
	bool deselectTower();
	std::list<Tower*>& getTowers() { return towers; }
	Tower* getTower(glm::vec2 pos);
	Tower* getSelectedTower() const { return selectedTower; }
	void clearTower();

	// Enemies
	void moveEnemies(float deltaTime);
	
	// Game, Rounds, Waves
	void startGame();
	void endGame();
	void pauseGame();
	void resumeGame();
	bool isActive() const { return active; }
	void nextRound();
	Round& getRound() { return currentRound; }
	Wave& getWave() const { return currentRound.getWave(); }

	// Game Speed
	void fastForward(float speedPercent);
	float getSpeed() const { return speed; }

	// Player
	void addMoney(int gain) { money += gain; }
	void loseLives(int livesLost) { lives -= livesLost; }
	int& getMoney() { return money; }
	int& getLives() { return lives; }
	std::string getStatus() const;
	
	// Hitboxes
	void activateHitbox() { activeHitbox = true; }
	void deactivateHitbox() { activeHitbox = false; }
	bool& areHitboxActive() { return activeHitbox; }

	// Managers
	Renderer& getRenderer() const { return renderer; }
	AudioManager& getAudioManager() { return audioManager; }

private:
	int money;
	int lives;
	float speed;

	Map map;

	std::list<Tower*> towers;
	Tower* selectedTower;
	
	// Rounds are kept for reset so currentRound is a copy to modify
	std::list<Round> rounds;
	std::list<Round*> roundStack;
	Round currentRound;
	
	bool active;
	bool activeHitbox;
	bool firstFrame = true;

	mutable Renderer renderer;
	AudioManager audioManager;
};

