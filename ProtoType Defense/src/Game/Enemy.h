#pragma once
#include "Entity.h"


class Enemy: public Entity
{
public:
	// BASE STATS
	static const int baseLife = 100;
	static const int baseSpeed = 50;

	static const uint32_t baseMoney = 20;
	static const uint32_t baseDamage = 1; // User Life loss if scapepublic:

	Enemy(const glm::vec3 pos, const uint32_t texID = 0, const uint32_t life = baseLife, const float speed = baseSpeed);
	Enemy(const Enemy& orig);
	~Enemy() override;

	int getHit(const uint32_t hit);
	void slow(const float slowPercentage);

	uint32_t getLife() const { return life; }
	float getSpeed() const { return speed; }
	static uint32_t getMoney() { return baseMoney; }
	static uint32_t getDamage() { return baseDamage; }

	void setLife(const uint32_t l) { life = l; }
	void setSpeed(const float spd) { speed = spd; }

private:

	uint32_t life;
	float speed;


	
};

