#include "Projectile.h"

#include <trigonometric.hpp>
#include "GlobalParameters.h"

using namespace glm;

static vec3 hitboxSize(32.0f);
static float spriteSize(16.0f);



Projectile::Projectile(const Tower* tower)
	: Projectile(tower, vec2(tower->getPosition2D()), hitboxSize, tower->getYaw(), tower->getPierce())
{
}

// 2D
Projectile::Projectile(const Tower* tower, vec2 position, vec2 size, float orientation, bool homming)
	: Entity(position, size, 1, spriteSize, orientation), m_Pierce(tower->getPierce()), m_Homming(homming), m_Tower(tower)
{
}

// 3D Flat Hitbox
Projectile::Projectile(const Tower* tower, vec3 position, vec2 size, float orientation, bool homming)
	: Entity(position, size, 1, spriteSize, orientation), m_Pierce(tower->getPierce()), m_Homming(homming), m_Tower(tower)
{
}

// 3D
Projectile::Projectile(const Tower* tower, vec3 position, vec3 size, float orientation, bool homming)
	: Entity(position, size, 1, spriteSize, orientation), m_Pierce(tower->getPierce()), m_Homming(homming), m_Tower(tower)
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


bool Projectile::impact(Hitbox& hitbox)
{
	if (m_Hitbox->collision(hitbox))
	{
		// IF Piercing:
		m_Pierce--;
		// If pierced stop pursuing and goes straight
		m_Homming = false;
		return true;
	}
	return false;
}

void Projectile::move(const float d)
{
	// If the Projectile is Homming, and his tower has an aimed enemy, it follows the enemy
	if (m_Homming && m_Tower->getEnemy() != nullptr)
	{
		Enemy& enemy = *m_Tower->getEnemy();
		const float predictiveCoefficient = enemy.getSpeed() / 2; // Distance towards the enemy movement
		
		glm::vec3 predictedPos(enemy.getPosition3D().x, enemy.getPosition3D().y, 0.0f);
		predictedPos.x += predictiveCoefficient * cos(enemy.getYaw());
		predictedPos.y += predictiveCoefficient * sin(enemy.getYaw());

		lookAt(predictedPos);
	}
	Entity::move(d);
}






