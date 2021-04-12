#include "Entity.h"
#include "GlobalParameters.h"

using namespace glm;

#define x position.x
#define y position.y
#define z position.z

Entity::Entity()
	: Entity(vec2(windowCenterX, windowCenterY))
{
}

Entity::Entity(vec2 position, const float yaw, const unsigned int texID)
	: Entity(vec3(position,0.0f), yaw, texID)
{
}

Entity::Entity(vec3 position, const float yaw, const unsigned int texID)
	: position(position), yaw(yaw), hitbox(nullptr), m_Sprite(position, 0.0f, 0.0f, texID)
{
}

Entity::Entity(vec2 position, vec2 size, const float yaw, const unsigned int texID)
	: Entity(vec3(position, 0.0f), size, yaw, texID)
{
}

Entity::Entity(vec3 position, vec2 size, const float yaw, const unsigned int texID)
	: Entity(position, vec3(size, 0.0f), yaw, texID)
{
}

Entity::Entity(vec3 position, vec3 size, const float yaw, const unsigned int texID)
	: position(position), yaw(yaw), hitbox(new Hitbox(position, size, yaw)), m_Sprite(position, 0.0f, degrees(yaw), texID)
{
}

Entity::~Entity()
{
	delete hitbox;
}

void Entity::setPosition(const glm::vec3 pos)
{
	position = pos;
	hitbox->setPosition(pos);
	m_Sprite.setPosition(pos);
}

void Entity::move(const float X, const float Y)
{
	x += X * cos(yaw);
	y += Y * sin(yaw);
}

void Entity::move(const float X, const float Y, const float Z)
{
	x += X * cos(yaw);
	y += Y * sin(yaw);
	z += Z;
}

void Entity::rotate(float X)
{
	// Normalized to [0,360] º
	if (X > 360 || X < 0) X -= floor(X / 360) * 360;
	yaw += rad(X);
	hitbox->rotate(x);
}
