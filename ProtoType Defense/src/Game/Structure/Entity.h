#pragma once
#include "pch.h"

#include "Hitbox.h"
#include "Sprite.h"

static int baseSpriteScale = 256;

class Entity
{
public:
	Entity();
	// No Hitbox
	Entity(glm::vec3 position, const uint32_t texID = 0, glm::vec2 spriteScale = glm::vec2(baseSpriteScale), const double yaw = 0);
	// Flat Hitbox
	Entity(glm::vec3 position, glm::vec2 size, const uint32_t texID = 0, glm::vec2 spriteScale = glm::vec2(baseSpriteScale), const double yaw = 0);
	// 3D Hitbox
	Entity(glm::vec3 position, glm::vec3 size, const uint32_t texID = 0, glm::vec2 textureSize = glm::vec2(baseSpriteScale), const double yaw = 0);

	virtual ~Entity();
	
	glm::vec2 getPosition2D() const { return glm::vec2(m_Position.x, m_Position.y); }
	glm::vec3 getPosition3D() const { return m_Position; }
	glm::vec2 getSize2D() const { return m_Hitbox->getSize2D(); }
	glm::vec3 getSize3D() const { return m_Hitbox->getPosition3D(); }
	Sprite& getSprite() const { return m_Sprite; }
	Hitbox& getHitbox() const { return *m_Hitbox; }
	double getYaw() const { return m_Yaw; }

	virtual void setPosition(const glm::vec3 pos);
	void setYaw(const float yaw) { m_Yaw = yaw; m_Sprite.setRotation(0); }
	
	void move(const float X, const float Y, const float Z = 0.0f);
	virtual void move(const float d);
	virtual void move(const float d, const double yaw);

	void rotate(float X); // X in Degrees
	void lookAt(glm::vec3 position);


protected:
	glm::vec3 m_Position;
	double m_Yaw; // radians

	Hitbox* m_Hitbox; // No necessary

	mutable Sprite m_Sprite;

};

