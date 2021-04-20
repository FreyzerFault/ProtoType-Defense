#include "Map.h"

using namespace glm;

Map::Map()
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
				pathTiles.emplace_back(&(tileMap.find(position)->second));
			}
		}
	}
	path = new Path(pathTiles);
}
