#pragma once

#include "Sprite.h"
#include "Platform.h"
#include "Entity.h"

class Tower : public Entity
{
public:
	// BASE STATS
	static const int baseDamage = 50;
	static const int baseAttackSpeed = 1;
	static const int baseProjectileSpeed = 100;
	static const int baseProjectilePierce = 1;
	static const int baseRange = 5;
	static const int baseCost = 200;
	static int numTowers; // STATIC = Se comparte entre todas las instancias

private:
	const unsigned int m_ID; // Unique
	int m_Damage;
	float m_AttackSpeed;
	float m_Range;
	float m_ProjectileSpeed;
	float m_ProjectilePierce;
	int m_Cost;

	Platform* m_Platform;

	
public:
	virtual void shoot() const;

public:
	Tower();
	Tower(unsigned int texID, Platform* platform);
	Tower(Platform* platform, int damage = baseDamage, float attackSpeed = baseAttackSpeed,
		float range = baseRange, float projectileSpeed = baseProjectileSpeed,
		float projectilePierce = baseProjectilePierce, int cost = baseCost, unsigned int texID = 0);
	Tower(const Tower& orig);
	Tower& operator=(const Tower& orig);
	virtual ~Tower() override;

	void dmgUp(const int percentage) { m_Damage += m_Damage * percentage / 100; }
	void speedUp(const float percentage) { m_AttackSpeed += m_AttackSpeed * percentage / 100; }
	void rangeUP(const float percentage) { m_Range += m_Range * percentage / 100; }
	void prSpeedUp(const float percentage) { m_ProjectileSpeed += m_ProjectileSpeed * percentage / 100; }
	void pierceUp(const float percentage) { m_ProjectilePierce += m_ProjectilePierce * percentage / 100; }

	int getDmg() const { return m_Damage; }
	float getSpd() const { return m_AttackSpeed; }
	float getRange() const { return m_Range; }
	float getPrSpd() const { return m_ProjectileSpeed; }
	float getPierce() const { return m_ProjectilePierce; }
	int getCost() const { return m_Cost; }

	void setDmg(const int dmg) { m_Damage = dmg; }
	void setSpd(const float spd) { m_AttackSpeed = spd; }
	void setRange(const float range) { m_Range = range; }
	void setPrSpd(const float prSpd) { m_ProjectileSpeed = prSpd; }
	void setPierce(const float pierce) { m_ProjectilePierce = pierce; }
	void setCost(const int cost) { m_Cost = cost; }

	bool placeIn(Platform& platform);
};

