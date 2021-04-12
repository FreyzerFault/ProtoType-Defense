#pragma once
#include <vec2.hpp>
#include <vec3.hpp>


class Hitbox
{
private:
	glm::vec3 position; // Center
	glm::vec3 size;
	float yaw;

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

	glm::vec2 getPosition2D() const { return glm::vec2(position); }
	glm::vec3 getPosition3D() const { return glm::vec3(position); }
	glm::vec2 getSize2D() const { return glm::vec2(size); }
	glm::vec3 getSize3D() const { return glm::vec3(size); }
	float getX() const { return position.x; }
	float getY() const { return position.y; }
	float getZ() const { return position.z; }
	float getsX() const { return size.x; }
	float getsY() const { return size.y; }
	float getsZ() const { return size.z; }

	void setPosition(const glm::vec3 pos) { position = pos; }
	

	void move(const float X, const float Y);
	void move(const float X, const float Y, const float Z);
	
	void rotate(float X);
};

