#pragma once

#include "Objects/Tower.h"
#include "Objects/Projectile.h"
#include "Objects/Enemy.h"

#include "Structure/Entity.h"
#include "Structure/Sprite.h"
#include "Structure/Hitbox.h"

#include "Map/Platform.h"
#include "Map/Tile.h"
#include "Map/Path.h"
#include "Map/Map.h"
#include "Map/Round.h"

#include "Renderer.h"

class GameController
{
public:
	GameController();

	void update(float deltaTime);
	void render(glm::mat4 mvp);
	void reset();

	// Round Control
	void startGame();
	void endGame();
	void nextRound();
	void pauseGame();
	void fastForward(float speedPercent);

	// Player Control
	void addMoney(int gain) { money += gain; }
	
	Round& getRound() { return currentRound; }
	Wave& getWave() const { return currentRound.getWave(); }
	Path& getPath() { return map.getPath(); }
	Renderer& getRenderer() const { return renderer; }

	int getMoney() const { return money; }
	float getSpeed() { return speed; }
	std::string getStatus() const;

	bool isActive() const { return active; }


private:
	int money;
	int lives;

	float speed;

	bool active;

	Map map;
	
	// Rounds are kept for reset so currentRound is a copy to modify
	std::list<Round> rounds;
	std::list<Round*> roundStack;
	Round currentRound;

	mutable Renderer renderer;

	bool firstFrame = true;
};

