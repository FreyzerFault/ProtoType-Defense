#pragma once
#include "Hitbox.h"
#include "Sprite.h"

static int baseSpriteScale = 128;

class Entity
{
public:
	Entity();
	// No Hitbox 2D
	Entity(glm::vec2 position, const uint32_t texID = 0, const float spriteScale = baseSpriteScale, const double yaw = 0);
	// No Hitbox 3D
	Entity(glm::vec3 position, const uint32_t texID = 0, const float spriteScale = baseSpriteScale, const double yaw = 0);
	// Flat Hitbox 2D
	Entity(glm::vec2 position, glm::vec2 size, const uint32_t texID = 0, const float spriteScale = baseSpriteScale, const double yaw = 0);
	// Flat Hitbox 3D
	Entity(glm::vec3 position, glm::vec2 size, const uint32_t texID = 0, const float spriteScale = baseSpriteScale, const double yaw = 0);
	// 3D Hitbox
	Entity(glm::vec3 position, glm::vec3 size, const uint32_t texID = 0, const float spriteScale = baseSpriteScale, const double yaw = 0);

	virtual ~Entity();
	
	glm::vec2 getPosition2D() const { return glm::vec2(m_Position.x, m_Position.y); }
	glm::vec3 getPosition3D() const { return m_Position; }
	glm::vec2 getSize2D() const { return m_Hitbox->getSize2D(); }
	glm::vec3 getSize3D() const { return m_Hitbox->getPosition3D(); }
	const Sprite& getSprite() const { return m_Sprite; }
	Hitbox& getHitbox() const { return *m_Hitbox; }
	double getYaw() const { return m_Yaw; }

	void setPosition(const glm::vec3 pos);
	
	void move(const float X, const float Y, const float Z = 0.0f);
	virtual void move(const float d);

	void rotate(float X); // X in Degrees
	void lookAt(glm::vec3 position);


protected:
	glm::vec3 m_Position;
	double m_Yaw; // radians

	Hitbox* m_Hitbox; // No necessary

	Sprite m_Sprite;

};

