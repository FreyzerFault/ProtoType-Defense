#include "Tile.h"

using namespace glm;

Tile::Tile()
	: Tile(vec2(0.0f))
{
}

Tile::Tile(glm::vec2 pos, float size, vec3 color)
	: position(pos), size(size), color(color), direction(Direction::right),
	  vertices{
		{{position.x,			position.y, 0.0f},			{color.r, color.g, color.b, 1.0f}},
		{{position.x + size,	position.y, 0.0f},			{color.r, color.g, color.b, 1.0f}},
		{{position.x + size,	position.y + size, 0.0f},	{color.r, color.g, color.b, 1.0f}},
		{{position.x,			position.y + size, 0.0f},	{color.r, color.g, color.b, 1.0f}},
	  }
{
}

Tile::Tile(glm::vec2 pos, Direction dir, float size, glm::vec3 color)
	: position(pos), size(size), color(color), direction(dir),
	vertices{
	  {{position.x,			position.y, 0.0f},			{color.r, color.g, color.b, 1.0f}},
	  {{position.x + size,	position.y, 0.0f},			{color.r, color.g, color.b, 1.0f}},
	  {{position.x + size,	position.y + size, 0.0f},	{color.r, color.g, color.b, 1.0f}},
	  {{position.x,			position.y + size, 0.0f},	{color.r, color.g, color.b, 1.0f}},
}
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
