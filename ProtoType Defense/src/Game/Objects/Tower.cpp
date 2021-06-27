#include "pch.h"
#include "Tower.h"

#include "AudioManager.h"
#include "Projectile.h"
#include "Map/Path.h"

using namespace glm;

int Tower::numTowers = 0;

const int Tower::baseDamage = 10;
const int Tower::baseAttackSpeed = 2;
const int Tower::baseProjectileSpeed = 300; // Optimal = Range * AtkSpeed
const int Tower::baseProjectilePierce = 1;
const int Tower::baseRange = 200;
const int Tower::baseCost = 200;

// Por defecto tendra las caracteristicas de un Piercer
Tower::Tower()
	: Tower(1, nullptr)
{
}

Tower::Tower(const int texID, Platform* platform)
	: Tower(platform, baseDamage, baseAttackSpeed, baseRange,
		baseProjectileSpeed, baseProjectilePierce, baseCost, texID)
{
}

Tower::Tower(Platform* platform, const int damage, float const attackSpeed, float const range,
	float const projectileSpeed, int const projectilePierce, const int cost, const int texID)
	: Entity(vec3(vec2(platform->getCenter()), 0.0f), texID, vec2(64.0f), 0.0f), // No Hitbox
     platform(platform),
     aimedEnemy(nullptr), damage(damage), atkSpd(attackSpeed),
     range(range), prjSpd(projectileSpeed),
     prjPierce(projectilePierce), cost(cost)
{
}

// Crea otra que solo varía en la ID
Tower::Tower(const Tower& orig)
	: Tower(orig.platform, orig.damage, orig.atkSpd, orig.range,
		orig.prjSpd, orig.prjPierce, orig.cost, orig.m_Sprite.getTexID())
{
}

Tower::~Tower()
{
	clearProjectiles();
}

// No modifica la ID
Tower& Tower::operator=(const Tower& orig)
{
	if (&orig != this)
	{
		this->damage = orig.damage;
		this->atkSpd = orig.atkSpd;
		this->range = orig.range;
		this->prjSpd = orig.prjSpd;
		this->prjPierce = orig.prjPierce;
		this->cost = orig.cost;
		this->m_Sprite = orig.m_Sprite;
	}
	return *this;
}

bool Tower::placeIn(Platform& platf)
{
	if (platf.placeTower(*this))
	{
		platform = &platf;
		setPosition(platf.getPosition());
		return true;
	}
	return false;
}

void Tower::sell() const
{
	platform->sellTower();
}

void Tower::shoot(float deltaTime)
{
	// Update ShootTimer
	if (shootTimer < 1 / atkSpd)
		shootTimer += deltaTime;
	
	// If ShootTimer reach the time needed, it can shoot
	if (shootTimer >= 1 / atkSpd) // [Speed] disparos / segundo
	{
		if (shoot())
		{
			// Reset the ShootTimer
			shootTimer -= 1 / atkSpd;
			AudioManager::playSoundInsta("laser");
		}

		// Remove the first Projectile like a queue if a projectile have passed the range radious
		// 
		// Nº projectiles in radious = AttackSpeed * Radious / ProjSpeed
		//	[Projs/secs] * [~pixels~] / [~pixels~/secs]  -->  [Projs] * [~secs~] / [~secs~]  -->  [Projectiles in radius]

		// If there are more projectiles than the possible within range + the piercing, the first one is deleted
		if (projectiles.size() > ceil(atkSpd * range / prjSpd) + prjPierce)
			projectiles.pop_front();
	}
}

bool Tower::shoot()
{
	if (enemyOnRange())
	{
		// Create a Projectile
		projectiles.emplace_back(this);
		projectiles.back().setHomming(true);
		return true;
	}
	return false;
}

void Tower::moveProjectiles(float deltaTime)
{
	for (Projectile& projectile : projectiles)
	{
		projectile.move(deltaTime * prjSpd);
	}
}


void Tower::aim()
{
	if (enemyOnRange())
		lookAt(aimedEnemy->getPosition3D());
}

void Tower::aim(Path& path)
{
	switch (priority)
	{
	case Priority::first:
		aimedEnemy = path.getFirstEnemy(m_Position, range);
		break;
	case Priority::last:
		aimedEnemy = path.getLastEnemy(m_Position, range);
		break;
	case Priority::strong:
		aimedEnemy = path.getStrongEnemy(m_Position, range);
		break;
	case Priority::weak:
		aimedEnemy = path.getWeakEnemy(m_Position, range);
		break;
	}

	aimPredictive(*aimedEnemy);
}

void Tower::aim(Enemy* enemy)
{
	aimedEnemy = enemy;
	
	aim();
}

void Tower::aimPredictive(Enemy& enemy)
{
	aimedEnemy = &enemy;
	
	if (enemyOnRange())
	{
		const float predictiveCoefficient = enemy.getSpeed() / 2; // Distance towards the enemy movement

		glm::vec3 predictedPos(enemy.getPosition3D().x, enemy.getPosition3D().y, 0.0f);
		predictedPos.x += predictiveCoefficient * cos(enemy.getYaw());
		predictedPos.y += predictiveCoefficient * sin(enemy.getYaw());

		lookAt(predictedPos);
	}
}

bool Tower::enemyOnRange() const
{
	if (aimedEnemy == nullptr) return false;

	// Distance between Enemy and tower must be < range
	const glm::vec2 enemyPos = aimedEnemy->getPosition2D();
	float distance = sqrt(pow(enemyPos.x - m_Position.x, 2) + pow(enemyPos.y - m_Position.y, 2));

	// Distance = tower.center -> enemy.center
	// Add enemy size to be more precise
	vec2 enemySize = aimedEnemy->getSize2D();
	distance -= enemySize.x < enemySize.y ? enemySize.x : enemySize.y;
	
	return distance < range;
}

void Tower::clearProjectiles()
{
	auto it = projectiles.begin();
	while (it != projectiles.end())
	{
		const auto itaux = it;
		++it;
		projectiles.erase(itaux);
		
	}
}

void Tower::draw(Renderer& renderer) const
{
	renderer.draw(m_Sprite);
}

void Tower::drawRangeCircle(Renderer& renderer) const
{
	if (selected)
	{
		renderer.drawCircumference(vec3(getPosition2D(), m_Position.z + 1.f), range, 360, vec4(1));
		renderer.drawCircle(vec3(getPosition2D(), m_Position.z - 0.5f), range, 360, vec4(0.2f));
	}
}

