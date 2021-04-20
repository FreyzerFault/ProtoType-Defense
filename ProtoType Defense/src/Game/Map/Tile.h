#pragma once
#include <vec2.hpp>
#include <vec3.hpp>

class Tile
{
struct Vertex {
	float position[3];
	float color[4];
};

public:
	Tile();
	Tile(glm::vec2 pos, float size = 32.0f, glm::vec3 color = glm::vec3(0.1f, 0.2f, 0.6f));

	glm::vec2 getPosition() const { return position; }
	float getSize() const { return size; }
	glm::vec3 getColor() const { return color; }

	glm::vec2 getCenter() const { return glm::vec2(position.x + size / 2, position.y + size / 2); }

private:
	glm::vec2 position;
	float size;
	glm::vec3 color;
	
	Vertex vertices[4];
	
};

