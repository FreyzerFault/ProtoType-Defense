#pragma once
#include <vec2.hpp>
#include <vec3.hpp>


class Hitbox
{
private:
	glm::vec3 m_Position; // Center
	glm::vec3 m_Size;
	float m_Yaw;

public:
	// 16x16 in Center of window
	Hitbox();
	// 2D Hitbox
	Hitbox(glm::vec2 position, glm::vec2 size, float yaw = 0.0f);
	// 3D Hitbox
	Hitbox(glm::vec3 position, glm::vec3 size, float yaw = 0.0f);

	// Checks if object collide with Hitbox
	bool collision(Hitbox& object);
	
	// SAT (Separating Axis Theorem) based Collision detector
	bool SATcollision(Hitbox& object);
	// Vertices for SAT collisions
	glm::vec2 vertices[4];
	void updateVertices();

	glm::vec2 getPosition2D() const { return glm::vec2(m_Position); }
	glm::vec3 getPosition3D() const { return glm::vec3(m_Position); }
	glm::vec2 getSize2D() const { return glm::vec2(m_Size); }
	glm::vec3 getSize3D() const { return glm::vec3(m_Size); }
	float getX() const { return m_Position.x; }
	float getY() const { return m_Position.y; }
	float getZ() const { return m_Position.z; }
	float getsX() const { return m_Size.x; }
	float getsY() const { return m_Size.y; }
	float getsZ() const { return m_Size.z; }

	void setPosition(const glm::vec3 pos) { m_Position = pos; }
	void setYaw(const float yaw) { m_Yaw = yaw; }
	
	
	void move(const float X, const float Y, const float Z = 0.0f);
	void move(const float d);
	
	void rotate(float X);
};

