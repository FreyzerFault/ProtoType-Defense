#pragma once
#include "Map/Tile.h"
#include "Structure/Entity.h"

class Path;

enum class TypeEnemy
{
	basic,
	tank,
	sneaky,
	flying
};

static std::string typeToString(const TypeEnemy& type)
{
	switch (type)
	{
	case TypeEnemy::basic:
		return "Basic";
	case TypeEnemy::tank:
		return "Tank";
	case TypeEnemy::sneaky:
		return "Sneaky";
	case TypeEnemy::flying:
		return "Flying";
	}
}

class Enemy: public Entity
{
public:
	// BASE STATS
	static const int baseLife = 100;
	static const int baseSpeed = 50;

	static const uint32_t baseMoney = 20;
	static const uint32_t baseDamage = 1; // User Life loss if scapepublic:

	Enemy(const glm::vec3 pos, float spriteScale = 32.0f, double yaw = 0, const uint32_t texID = 2, const uint32_t life = baseLife, const float speed = baseSpeed);
	Enemy(Tile& tile, float spriteScale = 32.0f, const uint32_t texID = 10, const uint32_t life = baseLife, const float speed = baseSpeed);
	~Enemy() override;

	int getHit(const uint32_t hit);
	void slow(const float slowPercentage);

	uint32_t getLife() const { return life; }
	float getSpeed() const { return speed; }
	static uint32_t getMoney() { return baseMoney; }
	static uint32_t getDamage() { return baseDamage; }

	void setTile(Tile* tileOcuppied) { tile = tileOcuppied; }
	Tile* getTile() const { return tile; }

	void setLife(const uint32_t l) { life = l; }
	void setSpeed(const float spd) { speed = spd; }

	void move(const float d) override;

private:

	uint32_t life;
	float speed;

	Tile* tile;

};

