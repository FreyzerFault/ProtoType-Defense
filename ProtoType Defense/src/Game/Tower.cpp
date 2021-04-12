#include "Tower.h"

#include <iostream>
#include <thread>

int Tower::numTowers = 0;

// Por defecto tendra las caracteristicas de un Piercer
Tower::Tower()
	: Tower(0, nullptr)
{
}

Tower::Tower(const unsigned int texID, Platform* platform)
	: Tower(platform, baseDamage, baseAttackSpeed, baseRange,
		baseProjectileSpeed, baseProjectilePierce, baseCost, texID)
{
}

Tower::Tower(Platform* platform, const int damage, float const attackSpeed, float const range,
	float const projectileSpeed, float const projectilePierce, const int cost, const unsigned int texID)
	: Entity(platform->getPosition(), 0.0f, texID), // No Hitbox
	m_ID(numTowers++), m_Damage(damage),
	m_AttackSpeed(attackSpeed), m_Range(range), m_ProjectileSpeed(projectileSpeed),
	m_ProjectilePierce(projectilePierce), m_Cost(cost),
	m_Platform(platform)
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


void doShoot() { std::cout << "Shoot" << std::endl; };

void Tower::shoot() const {
	if (m_Platform)
		std::cout << "Tower (" << m_ID << "): [Shoot]" << std::endl;
	else
		std::cout << "Tower (" << m_ID << "): [ERROR] Not placed" << std::endl;
}