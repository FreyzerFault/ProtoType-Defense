#pragma once
#include "Entity.h"


class Enemy: public Entity
{
public:
	// BASE STATS
	static const int baseLife = 100;
	static const int baseSpeed = 20;

	static const unsigned int baseMoney = 20;
	static const unsigned int baseDamage = 1; // User Life loss if scape

private:

	unsigned int life;
	float speed;

public:

	Enemy(const glm::vec3 pos, const unsigned int life = baseLife, const float speed = baseSpeed);
	Enemy(const Enemy& orig);
	~Enemy() override;

	int getHit(const unsigned int hit);
	void slow(const float slowPercentage);

	unsigned int getLife() const { return life; }
	float getSpeed() const { return speed; }
	static unsigned int getMoney() { return baseMoney; }
	static unsigned int getDamage() { return baseDamage; }

	void setLife(const unsigned int l) { life = l; }
	void setSpeed(const float spd) { speed = spd; }
	
};

