#pragma once
#include "pch.h"

#include "Renderer.h"

class Hitbox
{
public:
	// 16x16 in Center of window
	Hitbox();
	// Flat Hitbox
	Hitbox(glm::vec3 position, glm::vec2 size, float yaw = 0.0f);
	// 3D Hitbox
	Hitbox(glm::vec3 position, glm::vec3 size, float yaw = 0.0f);


	// COLLIDERS are calculated in 2D
	// 
	// Checks if object collide with Hitbox
	bool collision(Hitbox& object);
	// SAT (Separating Axis Theorem) based Collision detector
	bool SATcollision(Hitbox& object);
	// Vertices for SAT collisions
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
	void setYaw(const double yaw) { m_Yaw = yaw; }
	
	void move(const float X, const float Y, const float Z = 0.0f);
	void move(const float d);
	
	void rotate(float X);
	
	glm::mat4 getModelMatrix() const;

private:

	glm::vec3 m_Position; // Center
	glm::vec3 m_Size;
	double m_Yaw;

	// Position of vertices for SAT collision detector
	glm::vec2 vertices[4];

};

