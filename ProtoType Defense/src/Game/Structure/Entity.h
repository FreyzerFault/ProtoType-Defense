#pragma once
#include "Hitbox.h"
#include "Sprite.h"


class Entity
{
protected:
	glm::vec3 m_Position;
	float m_Yaw; // radians
	
	Hitbox* m_Hitbox; // No necessary

	Sprite m_Sprite;

public:
	Entity();
	// No Hitbox 2D
	Entity(glm::vec2 position, const float yaw = 0.0f, const unsigned int texID = 0);
	// No Hitbox 3D
	Entity(glm::vec3 position, const float yaw = 0.0f, const unsigned int texID = 0);
	// Flat Hitbox 2D
	Entity(glm::vec2 position, glm::vec2 size, const float yaw = 0.0f, const unsigned int texID = 0);
	// Flat Hitbox 3D
	Entity(glm::vec3 position, glm::vec2 size, const float yaw = 0.0f, const unsigned int texID = 0);
	// 3D Hitbox
	Entity(glm::vec3 position, glm::vec3 size, const float yaw = 0.0f, const unsigned int texID = 0);

	virtual ~Entity();
	
	glm::vec2 getPosition2D() const { return glm::vec2(m_Position.x, m_Position.y); }
	glm::vec3 getPosition3D() const { return m_Position; }
	glm::vec2 getSize2D() const { return m_Hitbox->getSize2D(); }
	glm::vec3 getSize3D() const { return m_Hitbox->getPosition3D(); }
	Sprite& getSprite() { return m_Sprite; }
	Hitbox& getHitbox() const { return *m_Hitbox; }
	float getYaw() const { return m_Yaw; }

	void setPosition(const glm::vec3 pos);
	
	void move(const float X, const float Y, const float Z = 0.0f);
	void move(const float d);

	void rotate(float X); // X in Degrees
	void lookAt(glm::vec3 position);
};

