#include "pch.h"
#include "Tile.h"

using namespace glm;

Tile::Tile()
	: Tile(vec2(0.0f))
{
}

Tile::Tile(glm::vec2 pos, float size, vec3 color)
	: position(pos), size(size), color(color), direction(Direction::right)
{
}

Tile::Tile(glm::vec2 pos, Direction dir, float size, glm::vec3 color)
	: position(pos), size(size), color(color), direction(dir)
{
}

double Tile::getYaw() const
{
	switch (direction)
	{
	case Direction::right:
		return 0;
	case Direction::up:
		return PI / 2;
	case Direction::left:
		return PI;
	case Direction::down:
		return 3 * PI / 2;
	}
	return 0;
}
