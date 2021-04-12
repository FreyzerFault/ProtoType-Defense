#include "Projectile.h"

#include <trigonometric.hpp>
#include "GlobalParameters.h"

using namespace glm;

static vec3 hitboxSize(16.0f);

Projectile::Projectile(const Tower* tower)
	: Projectile(tower, vec2(tower->getPosition2D()), hitboxSize, tower->getYaw(), tower->getPierce())
{
}

// 2D
Projectile::Projectile(const Tower* tower, vec2 position, vec2 size, float orientation, bool homming)
	: Entity(position, size, orientation), m_Pierce(tower->getPierce()), m_Homming(homming), m_Tower(tower)
{
}

// 3D Flat Hitbox
Projectile::Projectile(const Tower* tower, vec3 position, vec2 size, float orientation, bool homming)
	: Entity(position, size, orientation), m_Pierce(tower->getPierce()), m_Homming(homming), m_Tower(tower)
{
}

// 3D
Projectile::Projectile(const Tower* tower, vec3 position, vec3 size, float orientation, bool homming)
	: Entity(position, size, orientation), m_Pierce(tower->getPierce()), m_Homming(homming), m_Tower(tower)
{
}

Projectile::Projectile(const Projectile& orig) = default;

Projectile::~Projectile() = default;

Projectile& Projectile::operator=(const Projectile& orig)
{
	if (this != &orig)
	{
		m_Pierce = orig.m_Pierce;
		m_Homming = orig.m_Homming;
		m_Tower = orig.m_Tower;
	}
	return *this;
}


bool Projectile::Impact()
{
	// IF Piercing:
	m_Pierce--;

	// If pierced stop pursuing and goes straight
	m_Homming = false;

	return true;
}






