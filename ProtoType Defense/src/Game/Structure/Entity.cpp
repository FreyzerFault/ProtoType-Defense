#include "Entity.h"


#include "GlobalParameters.h"

using namespace glm;

#define x m_Position.x
#define y m_Position.y
#define z m_Position.z

Entity::Entity()
	: Entity(vec2(windowCenterX, windowCenterY))
{
}

Entity::Entity(vec2 position, const uint32_t texID, const float spriteScale, const double yaw)
	: Entity(vec3(position,0.0f), texID, spriteScale, yaw)
{
}

Entity::Entity(vec3 position, const uint32_t texID, const float spriteScale, const double yaw)
	: m_Position(position), m_Yaw(yaw), m_Hitbox(nullptr), m_Sprite(position, spriteScale, yaw, texID)
{
}

Entity::Entity(vec2 position, vec2 size, const uint32_t texID, const float spriteScale, const double yaw)
	: Entity(vec3(position, 0.0f), size, texID, spriteScale, yaw)
{
}

Entity::Entity(vec3 position, vec2 size, const uint32_t texID, const float spriteScale, const double yaw)
	: Entity(position, vec3(size, 0.0f), texID, spriteScale, yaw)
{
}

Entity::Entity(vec3 position, vec3 size, const uint32_t texID, const float spriteScale, const double yaw)
	: m_Position(position), m_Yaw(yaw), m_Hitbox(new Hitbox(position, size, yaw)), m_Sprite(position, spriteScale, yaw, texID)
{
}

Entity::~Entity()
{
	delete m_Hitbox;
}

void Entity::setPosition(const glm::vec3 pos)
{
	m_Position = pos;
	m_Hitbox->setPosition(pos);
	m_Sprite.setPosition(pos);
}

void Entity::move(const float X, const float Y, const float Z)
{
	x += X;
	y += Y;
	z += Z;
	m_Sprite.setPosition(m_Position);
	if (m_Hitbox != nullptr)
		m_Hitbox->setPosition(m_Position);
}

void Entity::move(const float d)
{
	x += d * cos(m_Yaw);
	y += d * sin(m_Yaw);
	
	m_Sprite.setPosition(m_Position);
	if (m_Hitbox != nullptr)
		m_Hitbox->setPosition(m_Position);
}


void Entity::rotate(float X)
{
	m_Yaw += X;
	// Normalized to [0,2PI] radians
	m_Yaw -= floor(m_Yaw / (2 * PI)) * 2*PI;
	
	if (m_Hitbox != nullptr)
		m_Hitbox->setYaw(m_Yaw);
	m_Sprite.setRotation(m_Yaw);
}

void Entity::lookAt(glm::vec3 p)
{
	// d = Distance Tower -> Enemy
	glm::vec3 d(p.s - x, p.t - y, 0.0f);
	// h = Hipotenusa, c = Cateto continuo
	double h = sqrt(pow(d.s, 2) + pow(d.t, 2));
	double c = d.s;
		
	m_Yaw = acos(c / h);
	// ACOS() returns always positive, so if yaw is over PI, it needs to be inverted
	if (d.t < 0)
		m_Yaw = 2 * PI - m_Yaw;

	if (m_Hitbox != nullptr)
		m_Hitbox->setYaw(m_Yaw);
	m_Sprite.setRotation(m_Yaw);
	
}


