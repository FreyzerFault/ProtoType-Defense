#include "Tile.h"

using namespace glm;

Tile::Tile()
	: Tile(vec2(0.0f))
{
}

Tile::Tile(glm::vec2 pos, float size, vec3 color)
	: position(pos), size(size), color(color),
	  vertices{
		{{position.x,			position.y, 0.0f},			{color.r, color.g, color.b, 1.0f}},
		{{position.x + size,	position.y, 0.0f},			{color.r, color.g, color.b, 1.0f}},
		{{position.x + size,	position.y + size, 0.0f},	{color.r, color.g, color.b, 1.0f}},
		{{position.x,			position.y + size, 0.0f},	{color.r, color.g, color.b, 1.0f}},
	  }
{
}
