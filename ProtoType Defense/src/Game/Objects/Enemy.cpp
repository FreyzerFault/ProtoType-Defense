#include "pch.h"
#include "Enemy.h"

#include "Map/Path.h"

using namespace glm;

static vec2 hitboxSize(64,64);

Enemy::Enemy(const vec3 pos, const int texID, double yaw, vec2 spriteScale, const int life, const GLfloat speed)
	: Entity(pos, spriteScale, texID, spriteScale, yaw),
	tile(nullptr), healthBar(pos, spriteScale.y / 2, spriteScale.x),
	life(life), iniLife(life), speed(speed), reward(baseReward), damage(baseDamage)
{
}

Enemy::Enemy(Tile& tile, const int texID, vec2 spriteScale, const int life, const GLfloat speed)
	: Entity(vec3(tile.getCenter(), 1.f), spriteScale, texID, spriteScale, tile.getYaw()),
	tile(&tile), healthBar(vec3(tile.getCenter(), 1.f), spriteScale.y / 2,spriteScale.x),
	life(life), iniLife(life), speed(speed), reward(baseReward), damage(baseDamage)
{
}

Enemy::~Enemy() = default;

int Enemy::getHit(GLfloat hitDmg)
{
	// If the damage is 0 don't flash red hit color
	if (hitDmg == 0)
	{
		framesHitCounter--;
		if (framesHitCounter <= 0)
		{
			hit = false;
			framesHitCounter = 20;
		}
	}
	else
	{
		framesHitCounter = 20;
		hit = true;
	}
	
	if (hitDmg > life)
		hitDmg = life;
	
	life -= hitDmg;
	healthBar.decrease(hitDmg / iniLife * 100);
	return life;
}

void Enemy::slow(const GLfloat slowPercentage)
{
	speed -= speed * slowPercentage / 100;
}

void Enemy::setPosition(glm::vec3 pos)
{
	m_Position = pos;
	m_Hitbox->setPosition(pos);
	m_Sprite.setPosition(pos);
	healthBar.setPosition(vec3(pos.x, pos.y + getSize2D().y / 2, pos.z));
	healthBar.reset();
}

// Checks if tile changed direction, and goes towards his direction when enemy reaches a position randomly near the center
void Enemy::move(const GLfloat d)
{
	if (tile != nullptr)
	{
		// When enemy reach new Tile, check yaw, if direction is different wait for reaching somewhere near center of tile
		if (tile->getYaw() != m_Yaw)
		{
			// Search for random range from the center of tile where they can change direction
			
			const int tileSize = round(tile->getSize());
			const vec2 center = tile->getCenter();

			// Random offset from center to 1/4 and -1/4 tileSize 
			const int maxOffset = tileSize / 2;
			std::srand(std::time(nullptr));
			const int offset = std::rand() % (maxOffset - maxOffset / 2);

			// Enemy will only change direction if it enters on tilesize/10 range of the random offset
			// 
			// Horizontal --> Vertical
			if (tile->getDirection() == Tile::Direction::down || tile->getDirection() == Tile::Direction::up)
				if (std::abs(m_Position.x - (center.x + offset)) < tileSize / 10)
					// Start moving towards Tile direction
					Entity::move(d, tile->getYaw());
				else
					Entity::move(d);
			
				// Vertical --> Horizontal
			else if (tile->getDirection() == Tile::Direction::left || tile->getDirection() == Tile::Direction::right)
				if (std::abs(m_Position.y - (center.y + offset)) < tileSize / 10)
					// Start moving towards Tile direction
					Entity::move(d, tile->getYaw());
				else
					Entity::move(d);

		}
		else
			Entity::move(d);
	}
	else
		Entity::move(d);

	// HEALTH BAR
	healthBar.move(d, m_Yaw);
}

void Enemy::draw(Renderer& renderer) const
{
	// Flashy red color when got hit
	if (hit)
		renderer.getShaderManager().setUniform4f("u_BlendColor", 1.f, 0.f, 0.f, 0.5f);

	renderer.draw(m_Sprite);
	
	renderer.getShaderManager().setUniform4f("u_BlendColor", 0.f, 0.f, 0.f, 0.f);
	
	healthBar.draw(renderer);
}

void Enemy::drawHitbox(Renderer& renderer) const
{
	renderer.draw(*m_Hitbox);
}

bool Enemy::inRange(glm::vec2 center, GLfloat range) const
{
	vec2 enemySize = getSize2D();
	const GLfloat margin = enemySize.x < enemySize.y ? enemySize.x : enemySize.y; // Smallest size as enemy MARGIN

	return distance(vec2(m_Position), center) - margin < range; // If enters inside the range
}
