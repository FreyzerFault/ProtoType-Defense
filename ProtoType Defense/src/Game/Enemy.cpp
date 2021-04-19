#include "Enemy.h"

using namespace glm;

static vec2 hitboxSize(32,32);

Enemy::Enemy(const vec3 pos, const uint32_t texID, const unsigned life, const float speed)
	: Entity(pos, hitboxSize, 0.0f, texID), life(life), speed(speed)
{
}

Enemy::Enemy(const Enemy& orig)
	: Entity(orig.m_Position, orig.getSize2D()), life(orig.life), speed(orig.speed)
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
