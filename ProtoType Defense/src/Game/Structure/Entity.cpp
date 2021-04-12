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

Entity::Entity(vec2 position, const float yaw, const unsigned int texID)
	: Entity(vec3(position,0.0f), yaw, texID)
{
}

Entity::Entity(vec3 position, const float yaw, const unsigned int texID)
	: m_Position(position), m_Yaw(yaw), m_Hitbox(nullptr), m_Sprite(position, 1.0f, 0.0f, texID)
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
	: m_Position(position), m_Yaw(yaw), m_Hitbox(new Hitbox(position, size, yaw)), m_Sprite(position, 1.0f, yaw, texID)
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
	// Position X,Y
	float X = p.s, Y = p.t;
	// h = Hipotenusa, c = Cateto continuo
	float h = sqrt(pow(X - x, 2) + pow(Y - y, 2));
	float c = X - x;
	
	m_Yaw = acos(c / h);

	if (m_Hitbox != nullptr)
		m_Hitbox->setYaw(m_Yaw);
	m_Sprite.setRotation(m_Yaw);
	
}


