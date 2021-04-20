#include "Tower.h"
#include "Projectile.h"

#include <iostream>
#include <thread>

#include "GlobalParameters.h"

int Tower::numTowers = 0;

const int Tower::baseDamage = 50;
const int Tower::baseAttackSpeed = 3;
const int Tower::baseProjectileSpeed = 300; // Optimal = Range * AtkSpeed
const int Tower::baseProjectilePierce = 1;
const int Tower::baseRange = 300;
const int Tower::baseCost = 200;

// Por defecto tendra las caracteristicas de un Piercer
Tower::Tower()
	: Tower(0, nullptr)
{
}

Tower::Tower(const uint32_t texID, Platform* platform)
	: Tower(platform, baseDamage, baseAttackSpeed, baseRange,
		baseProjectileSpeed, baseProjectilePierce, baseCost, texID)
{
}

Tower::Tower(Platform* platform, const int damage, float const attackSpeed, float const range,
	float const projectileSpeed, int const projectilePierce, const int cost, const uint32_t texID)
	: Entity(platform->getPosition(), texID, 32.0f, 0.0f), // No Hitbox
	m_ID(numTowers++), m_Damage(damage),
	m_AttackSpeed(attackSpeed), m_Range(range), m_ProjectileSpeed(projectileSpeed),
	m_ProjectilePierce(projectilePierce), m_Cost(cost),
	m_Platform(platform), aimedEnemy(nullptr)
{
}

// Crea otra que solo varía en la ID
Tower::Tower(const Tower& orig)
	: Tower(orig.m_Platform, orig.m_Damage, orig.m_AttackSpeed, orig.m_Range,
		orig.m_ProjectileSpeed, orig.m_ProjectilePierce, orig.m_Cost, orig.m_Sprite.getTexID())
{
}

// No modifica la ID
Tower& Tower::operator=(const Tower& orig)
{
	if (&orig != this)
	{
		this->m_Damage = orig.m_Damage;
		this->m_AttackSpeed = orig.m_AttackSpeed;
		this->m_Range = orig.m_Range;
		this->m_ProjectileSpeed = orig.m_ProjectileSpeed;
		this->m_ProjectilePierce = orig.m_ProjectilePierce;
		this->m_Cost = orig.m_Cost;
		this->m_Sprite = orig.m_Sprite;
	}
	return *this;
}

Tower::~Tower() = default;

bool Tower::placeIn(Platform& platform)
{
	if (platform.placeTower(*this))
	{
		m_Platform = &platform;
		setPosition(platform.getPosition());
		return true;
	}
	return false;
}


void Tower::shoot() {
	if (m_Platform)
	{
		m_Projectiles.emplace_back(this);
		m_Projectiles.back().setHomming(true);
		
		// Remove the first Projectile like a queue if a projectile have passed the range radious
		// 
		// Nº projectiles in radious = AttackSpeed * Radious / ProjSpeed
		//	[Projs/secs] * [~pixels~] / [~pixels~/secs]  -->  [Projs] * [~secs~] / [~secs~]  -->  [Projectiles in radius]
		
		if (m_Projectiles.size() > ceil(m_AttackSpeed * m_Range / m_ProjectileSpeed));
			//m_Projectiles.pop_front();

	}
	else
		std::cout << "Tower (" << m_ID << "): [ERROR] Not placed in any platform" << std::endl;
}



void Tower::aim()
{
	// Aim an Enemy from the Path

	
	lookAt(aimedEnemy->getPosition3D());
}

void Tower::aim(Enemy& enemy)
{
	aimedEnemy = &enemy;
	
	lookAt(aimedEnemy->getPosition3D());
}

void Tower::aimPredictive(Enemy& enemy)
{
	aimedEnemy = &enemy;
	
	const float predictiveCoefficient = enemy.getSpeed() / 2; // Distance towards the enemy movement
	
	glm::vec3 predictedPos(enemy.getPosition3D().x, enemy.getPosition3D().y, 0.0f);
	predictedPos.x += predictiveCoefficient * cos(enemy.getYaw());
	predictedPos.y += predictiveCoefficient * sin(enemy.getYaw());
	
	lookAt(predictedPos);
}

