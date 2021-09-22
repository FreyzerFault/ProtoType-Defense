#include "pch.h"
#include "Projectile.h"

using namespace glm;

static vec2 hitboxSize(24.f, 16.f);
static vec2 spriteSize(24.f);

static int texID = 0;

static GLfloat delayImpact = 0.5;


Projectile::Projectile(const Tower* tower)
	: Projectile(tower, vec3(tower->getPosition3D()), hitboxSize, tower->getYaw(), tower->getPierce())
{
}

// 2D
Projectile::Projectile(const Tower* tower, vec2 position, vec2 size, GLfloat orientation, bool homming)
	: Entity(vec3(position, 2.0f), size, texID, spriteSize, orientation), m_Pierce(tower->getPierce()), m_Homing(homming), m_Tower(tower)
{
}

// 3D Flat Hitbox
Projectile::Projectile(const Tower* tower, vec3 position, vec2 size, GLfloat orientation, bool homming)
	: Entity(position, size, texID, spriteSize, orientation), m_Pierce(tower->getPierce()), m_Homing(homming), m_Tower(tower)
{
}

// 3D
Projectile::Projectile(const Tower* tower, vec3 position, vec3 size, GLfloat orientation, bool homming)
	: Entity(position, size, texID, spriteSize, orientation), m_Pierce(tower->getPierce()), m_Homing(homming), m_Tower(tower)
{
}

Projectile::Projectile(const Projectile& orig) = default;

Projectile::~Projectile() = default;

Projectile& Projectile::operator=(const Projectile& orig)
{
	if (this != &orig)
	{
		m_Pierce = orig.m_Pierce;
		m_Homing = orig.m_Homing;
		m_Tower = orig.m_Tower;
	}
	return *this;
}


bool Projectile::impact(Hitbox& hitbox)
{
	if (m_Hitbox->collision(hitbox))
	{
		for (Hitbox* hb : impacted)
		{
			// If still colliding the same hitbox, don't trigger the hit
			if (hb == &hitbox)
				return false;
		}
		// If first time hitting hitbox
		m_Pierce--;

		// If pierced stop pursuing and goes straight
		m_Homing = false;

		impacted.push_back(&hitbox);

		return true;
	}
	
	auto it = impacted.begin();
	while (it != impacted.end())
	{
		// When stops colliding remove from the list so the projectile can hit later
		if (*it == &hitbox)
		{
			it = impacted.erase(it);
			m_Homing = true;
		}
		else
			++it;
    }

	return false;
}

Enemy* Projectile::impact(std::list<Enemy>& enemies)
{
	for (Enemy& enemy : enemies)
	{
		if (impact(enemy.getHitbox()))
			return &enemy;
	}
	return nullptr;
}

void Projectile::move(const GLfloat d)
{
	// If the Projectile is Homming, and his tower has an aimed enemy, it follows the enemy
	if (m_Homing && m_Tower->getEnemy() != nullptr)
	{
		Enemy& enemy = *m_Tower->getEnemy();
		const GLfloat predictiveCoefficient = enemy.getSpeed() / 2; // Distance towards the enemy movement
		
		glm::vec3 predictedPos(enemy.getPosition3D().x, enemy.getPosition3D().y, 0.0f);
		predictedPos.x += predictiveCoefficient * cos(enemy.getYaw());
		predictedPos.y += predictiveCoefficient * sin(enemy.getYaw());

		// Check the angle between Projectile Direction and Direction towards Enemy
		const vec2 projToEnemyDir = normalize(vec2(predictedPos - m_Position));
		const vec2 projMovementDir = vec2(cos(m_Yaw), sin(m_Yaw));
		const GLfloat angle = orientedAngle(projMovementDir, projToEnemyDir);
		
		// If angle is to big, Projectile moves towards a minimun angle
		const GLfloat minAngle = d / 100;
		if (angle > minAngle)
			predictedPos = vec3(vec2(m_Position) + glm::rotate(projMovementDir, minAngle), predictedPos.z);
		
		lookAt(predictedPos);
	}
	Entity::move(d);
}






