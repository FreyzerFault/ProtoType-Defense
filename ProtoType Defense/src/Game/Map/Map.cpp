#include "Map.h"

#define right Tile::Direction::right
#define left Tile::Direction::left
#define up Tile::Direction::up
#define down Tile::Direction::down

using namespace glm;

Map::Map()
	: Map(vec2(32, 16))
{
}

Map::Map(glm::vec2 dimension)
	: dimension(32, 16), tileSize(32)
{
	for (int i = 0; i < dimension.x; i++)
	{
		for (int j = 0; j < dimension.y; j++)
		{
			vec2 position(i * tileSize, j * tileSize);
			tileMap.try_emplace(position, position, tileSize);

			// Straight Path in the middle
			if (j == round(dimension.y / 2))
			{
				Tile& tile = tileMap.find(position)->second;
				tile.setDirection(right);
				pathTiles.emplace_back(&(tileMap.find(position)->second));
			}
		}
	}
	path = new Path(pathTiles);
}
