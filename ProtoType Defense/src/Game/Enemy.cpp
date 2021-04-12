#include "Enemy.h"

using namespace glm;

static vec2 hitboxSize(32,32);

Enemy::Enemy(const vec3 pos, const unsigned life, const float speed)
	: Entity(pos, hitboxSize), life(life), speed(speed)
{
}

Enemy::Enemy(const Enemy& orig)
	: Entity(orig.position, orig.getSize2D()), life(orig.life), speed(orig.speed)
{
}

Enemy::~Enemy() = default;

int Enemy::getHit(const unsigned int hit)
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
