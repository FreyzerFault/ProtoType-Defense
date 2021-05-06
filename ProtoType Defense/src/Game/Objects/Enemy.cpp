#include "Enemy.h"

#include "Map/Path.h"

using namespace glm;

static vec2 hitboxSize(32,32);

Enemy::Enemy(const vec3 pos, float spriteScale, double yaw, const uint32_t texID, const unsigned life, const float speed)
	: Entity(pos, hitboxSize, texID, spriteScale, yaw), life(life), speed(speed), tile(nullptr)
{
}

Enemy::Enemy(Tile& tile, float spriteScale, const uint32_t texID, const uint32_t life, const float speed)
	: Entity(tile.getCenter() , hitboxSize, texID, spriteScale, tile.getYaw()), life(life), speed(speed), tile(&tile)
{
}

Enemy::~Enemy() = default;

int Enemy::getHit(const uint32_t hit)
{
	if (life <= hit)
		life = 0;
	else
		life -= hit;
	return life;
}

void Enemy::slow(const float slowPercentage)
{
	speed -= speed * slowPercentage / 100;
}

void Enemy::move(const float d)
{
	if (tile != nullptr)
		Entity::move(d, tile->getYaw());
	Entity::move(d);
}
