#pragma once
#include "pch.h"

#include "Structure/Entity.h"
#include "Map/Platform.h"
#include "Objects/Enemy.h"

class Projectile;

enum class TypeTower
{
	basic,
	piercer,
	bomb,
	sniper,
	antifly
};

enum class Priority
{
	first, last, strong, weak
};

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

public:
	Tower();
	Tower(int texID, Platform* platform);
	Tower(Platform* platform, int damage = baseDamage, float attackSpeed = baseAttackSpeed,
		float range = baseRange, float projectileSpeed = baseProjectileSpeed,
		int projectilePierce = baseProjectilePierce, int cost = baseCost, int texID = 1);
	Tower(const Tower& orig);
	virtual ~Tower();
	Tower& operator=(const Tower& orig);


	
	// Shooting
	void shoot(float deltaTime);
	bool shoot();
	
	void updateShootTimer(float deltaTime) { shootTimer += deltaTime; }
	void resetShootTimer() { shootTimer -= 1 / atkSpd; }
	float getShootTimer() const { return shootTimer; }
	
	void aim();
	void aim(Path& path);
	void aim(Enemy* enemy);
	void aimPredictive(Enemy& enemy);
	bool enemyOnRange() const;

	void moveProjectiles(float deltaTime);
	std::list<Projectile>& getProjectiles() { return projectiles; }
	void clearProjectiles();


	// Enemy Priority
	void setPriority(Priority pr) { priority = pr; }
	Priority getPriority() const { return priority; }


	
	// Player Selection
	void select() { selected = true; }
	void deselect() { selected = false; }
	bool isSelected() const { return selected; }

	

	// Drawing
	void draw(Renderer& renderer) const;
	void drawRangeCircle(Renderer& renderer) const;

	Enemy* getEnemy() const { return aimedEnemy; }


	
	// Stats
	int getDmg() const { return damage; }
	float getSpd() const { return atkSpd; }
	float getRange() const { return range; }
	float getPrSpd() const { return prjSpd; }
	int getPierce() const { return prjPierce; }
	int getCost() const { return cost; }

	void setDmg(const int dmg) { damage = dmg; }
	void setSpd(const float spd) { atkSpd = spd; }
	void setRange(const float rng) { range = rng; }
	void setPrSpd(const float prSpd) { prjSpd = prSpd; }
	void setPierce(const int pierce) { prjPierce = pierce; }
	void setCost(const int c) { cost = c; }

	void dmgUp(const int dmg) { damage += dmg; }
	void speedUp(const float percentage) { atkSpd += atkSpd * percentage / 100; }
	void rangeUP(const float percentage) { range += range * percentage / 100; }
	void prSpeedUp(const float percentage) { prjSpd += prjSpd * percentage / 100; }
	void pierceUp(const int pierce) { prjPierce += pierce; }

	
	// Platform
	bool placeIn(Platform& platf);
	Platform* getPlatform() const { return platform; }
	void sell() const;

private:
	Platform* platform;

	std::list<Projectile> projectiles;

	Enemy* aimedEnemy;
	
	Priority priority = Priority::first;

	
	bool selected = false;
	
	float shootTimer = 0;
	
	int damage;
	float atkSpd;
	float range;
	float prjSpd;
	int prjPierce;
	int cost;
};
