#pragma once
#include "pch.h"

#include "GlobalParameters.h"

class Tile
{
public:

	enum class Direction
	{
		left, right, up, down
	};

	Tile();
	Tile(glm::vec2 pos, GLfloat size = 32.0f, glm::vec3 color = glm::vec3(0.1f, 0.2f, 0.6f));
	Tile(glm::vec2 pos, Direction dir, GLfloat size = 32.0f, glm::vec3 color = glm::vec3(0.1f, 0.2f, 0.6f));

	glm::vec2 getPosition() const { return position; }
	GLfloat getSize() const { return size; }
	glm::vec3 getColor() const { return color; }

	Direction getDirection() const { return direction; }
	void setDirection(Direction dir) { direction = dir; }

	glm::vec2 getCenter() const { return glm::vec2(position.x + size / 2, position.y + size / 2); }

	// Radians of direction
	double getYaw() const;

private:
	glm::vec2 position;
	GLfloat size;
	glm::vec3 color;

	// Direction that will go an Enemy above it
	Direction direction;
	
};

