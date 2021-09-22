#pragma once
#include "pch.h"

#include "Renderer.h"

class Hitbox
{
public:
	// 16x16 in Center of window
	Hitbox();
	// Flat Hitbox
	Hitbox(glm::vec3 position, glm::vec2 size, GLfloat yaw = 0.0f);
	// 3D Hitbox
	Hitbox(glm::vec3 position, glm::vec3 size, GLfloat yaw = 0.0f);


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
	GLfloat getX() const { return m_Position.x; }
	GLfloat getY() const { return m_Position.y; }
	GLfloat getZ() const { return m_Position.z; }
	GLfloat getsX() const { return m_Size.x; }
	GLfloat getsY() const { return m_Size.y; }
	GLfloat getsZ() const { return m_Size.z; }

	void setPosition(const glm::vec3 pos) { m_Position = pos; }
	void setYaw(const double yaw) { m_Yaw = yaw; }
	
	void move(const GLfloat X, const GLfloat Y, const GLfloat Z = 0.0f);
	void move(const GLfloat d);
	
	void rotate(GLfloat X);
	
	glm::mat4 getModelMatrix() const;

private:

	glm::vec3 m_Position; // Center
	glm::vec3 m_Size;
	double m_Yaw;

	// Position of vertices for SAT collision detector
	glm::vec2 vertices[4];

};

