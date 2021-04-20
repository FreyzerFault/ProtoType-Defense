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
	
	void render(glm::mat4 mvp);
	
	void startGame();
	void endGame() const;
	void nextRound();
	void sendEnemy() const;
	void fastForward(float speedPercent);

	Round& getRound() const { return *currentRound; }
	Wave& getWave() const { return currentRound->getWave(); }
	Path& getPath() const { return map.getPath(); }
	Renderer& getRenderer() const { return renderer; }

	void addMoney(int gain) { money += gain; }
	int getMoney() const { return money; }

	std::string getStatus() const;

	bool isActive() const { return active; }


private:
	int money;
	int lives;

	float speed;

	bool active;

	Map map;
	std::list<Platform> platforms;
	std::list<Round> rounds;
	Round* currentRound;

	mutable Renderer renderer;
};

