#pragma once
#ifndef Tower_H
#define Tower_H

#include <list>

#include "Entity.h"
#include "Platform.h"
#include "Enemy.h"

class Projectile;


class Tower : public Entity
{
public:
	// BASE STATS
	static const int baseDamage;
	static const int baseAttackSpeed;
	static const int baseProjectileSpeed; // Optimal = Range * AtkSpeed
	static const int baseProjectilePierce;
	static const int baseRange;
	static const int baseCost;
	
	static int numTowers; // STATIC = Se comparte entre todas las instancias

private:
	const unsigned int m_ID; // Unique
	int m_Damage;
	float m_AttackSpeed;
	float m_Range;
	float m_ProjectileSpeed;
	int m_ProjectilePierce;
	int m_Cost;

	Platform* m_Platform;

	std::list<Projectile> m_Projectiles;

	Enemy* aimedEnemy;
	
public:
	Tower();
	Tower(unsigned int texID, Platform* platform);
	Tower(Platform* platform, int damage = baseDamage, float attackSpeed = baseAttackSpeed,
		float range = baseRange, float projectileSpeed = baseProjectileSpeed,
		int projectilePierce = baseProjectilePierce, int cost = baseCost, unsigned int texID = 0);
	Tower(const Tower& orig);
	Tower& operator=(const Tower& orig);
	virtual ~Tower() override;

	std::list<Projectile>& getProjectiles() { return m_Projectiles; }

	int getDmg() const { return m_Damage; }
	float getSpd() const { return m_AttackSpeed; }
	float getRange() const { return m_Range; }
	float getPrSpd() const { return m_ProjectileSpeed; }
	int getPierce() const { return m_ProjectilePierce; }
	int getCost() const { return m_Cost; }

	void setDmg(const int dmg) { m_Damage = dmg; }
	void setSpd(const float spd) { m_AttackSpeed = spd; }
	void setRange(const float range) { m_Range = range; }
	void setPrSpd(const float prSpd) { m_ProjectileSpeed = prSpd; }
	void setPierce(const int pierce) { m_ProjectilePierce = pierce; }
	void setCost(const int cost) { m_Cost = cost; }

	void dmgUp(const int damage) { m_Damage += damage; }
	void speedUp(const float percentage) { m_AttackSpeed += m_AttackSpeed * percentage / 100; }
	void rangeUP(const float percentage) { m_Range += m_Range * percentage / 100; }
	void prSpeedUp(const float percentage) { m_ProjectileSpeed += m_ProjectileSpeed * percentage / 100; }
	void pierceUp(const int pierce) { m_ProjectilePierce += pierce; }

	bool placeIn(Platform& platform);

	void shoot();
	void aim();
	void aim(Enemy& enemy);
	// Predict movement
	void aimPredictive(Enemy& enemy);
};

#endif