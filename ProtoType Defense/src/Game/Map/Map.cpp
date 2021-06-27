#include "pch.h"
#include "Map.h"

#include "Objects/Projectile.h"

#define right Tile::Direction::right
#define left Tile::Direction::left
#define up Tile::Direction::up
#define down Tile::Direction::down

using namespace glm;


Map::Map(Renderer* renderer)
	: Map(vec2(32, 16), renderer)
{
}

Map::Map(glm::vec2 dimension, Renderer* renderer)
	: dimension(dimension), tileSize(64), path(renderer)
{
	vertices = new Vertex[dimension.x * dimension.y * 4];
	indices = new uint32_t[dimension.x * dimension.y * 6];


	// TILES
	for (int i = 0; i < dimension.y; i++)
		for (int j = 0; j < dimension.x; j++)
		{
			vec3 position(j * tileSize, i * tileSize, -5.0f);
			tileMap.try_emplace(position, position, tileSize);
		}

	// PATH
	// 
	// Start RIGHT
	int y = round(dimension.y / 2);
	const int maxX = dimension.x / 2; // Right
	for (int i = 0; i < dimension.x; i++)
	{
		vec3 position(i * tileSize, y * tileSize, -5.0f);
		if (i < maxX) // [0, max)
		{
			addTileToPath(position, right);
			if (i == 0)
				path.setFirstTile(&tileMap.at(vec2(position)));

			addTileVertexData(i, y, position, colorPath);
		}
	}

	// Goes DOWN
	const int x = round(dimension.x / 2); // Column
	const int maxY = dimension.y / 2; // Top
	const int minY = dimension.y / 4; // Bottom
	for (int i = dimension.y - 1; i >= 0; i--)
	{
		const vec3 position(x * tileSize, i * tileSize, -5.0f);
		if (i <= maxY && i > minY) // [top, bottom)
		{
			addTileToPath(position, down);

			addTileVertexData(x, i, position, colorPath);
		}
	}

	// Goes RIGHT
	y = round(dimension.y / 4); // Column
	const int minX = dimension.y / 2; // Left
	for (int i = 0; i < dimension.x; i++)
	{
		const vec3 position(i * tileSize, y * tileSize, -5.0f);
		if (i >= minX) // [dimension.x/2, dimension.x)
		{
			addTileToPath(position, right);

			addTileVertexData(i, y, position, colorPath);
		}
	}

	// PLATFORMS
	for (int i = 0; i < dimension.y; i++)
		for (int j = 0; j < dimension.x; j++)
		{
			const vec3 position(j * tileSize, i * tileSize, -5.0f);

			if (!path.isPath(position))
			{
				platforms.try_emplace(vec2(position), position, tileSize);
				addTileVertexData(j, i, position, colorPlatform);
			}
		}

}

void Map::setupRendering(Renderer& renderer)
{
	VBO.setData(vertices, dimension.x * dimension.y * sizeof(Vertex) * 4, GL_STATIC_DRAW);
	layout.Push<float>(3);
	layout.Push<float>(4);
	VAO.addBuffer(VBO, layout);
	IBO.setIndices(indices, dimension.x * dimension.y * 6);
}

void Map::draw(Renderer& renderer)
{
	renderer.draw(VAO, IBO, "NoTexture");
}

void Map::drawTowers(Renderer& renderer)
{
	for (auto& tuple : platforms)
	{
		Platform& platform = tuple.second;

		if (!platform.isEmpty())
		{
			Tower* tower = platform.getTower();
			tower->draw(renderer);

			// PROJECTILES
			for (Projectile& projectile : tower->getProjectiles())
			{
				renderer.draw(projectile.getSprite());
			}
		}
	}
}

void Map::drawEnemies(Renderer& renderer)
{
	for (Enemy* enemy : path.getEnemyList())
	{
		enemy->draw(renderer);
	}
}

void Map::drawTowerRange(Renderer& renderer)
{
	for (auto& tuple : platforms)
	{
		Platform& platform = tuple.second;

		if (!platform.isEmpty())
		{
			Tower* tower = platform.getTower();
			tower->drawRangeCircle(renderer);
		}
	}
}

void Map::drawHitboxes(Renderer& renderer)
{
	for (auto& tuple : platforms)
	{
		Platform& platform = tuple.second;

		if (!platform.isEmpty())
		{
			// PROJECTILES
			for (Projectile& projectile : platform.getTower()->getProjectiles())
			{
				renderer.draw(projectile.getHitbox());
			}
		}
	}
	path.getEnemyList();
	for (Enemy* enemy : path.getEnemyList())
	{
		enemy->drawHitbox(renderer);
	}
}

glm::vec2 Map::getTilePos(glm::vec2 pos) const
{
	// Tile Scale Position (1 unit = tilesize)
	const vec2 tileScalePos = floor(pos / tileSize);
	const vec2 tilePos = tileScalePos * tileSize;
	return tilePos;
}

Platform* Map::getPlatform(glm::vec2 pos)
{
	const vec2 tilePos = getTilePos(pos);
	if (platforms.find(tilePos) != platforms.end())
		return &platforms.at(getTilePos(tilePos));
	return nullptr;
}

Tile* Map::getTile(glm::vec2 pos)
{
	auto it = tileMap.find(getTilePos(pos));
	if ( it == tileMap.end())
		return nullptr;
	return &it->second;
}

void Map::addTileVertexData(int tileX, int tileY, vec3 position, vec3 color) const
{
	// Index of the tile
	const uint32_t numTile = tileY * dimension.x + tileX;

	const float quadSize = tileSize - 4;

	float x = position.x;
	float y = position.y;
	float z = position.z;

	vertices[numTile * 4 + 0] = { {position.x,				position.y,				z},	{color.r, color.g, color.b, 1.0f} };
	color += 0.03f;
	vertices[numTile * 4 + 1] = { {position.x + quadSize,	position.y,				z},	{color.r, color.g, color.b, 1.0f} };
	vertices[numTile * 4 + 2] = { {position.x + quadSize,	position.y + quadSize,	z},	{color.r, color.g, color.b, 1.0f} };
	vertices[numTile * 4 + 3] = { {position.x,				position.y + quadSize,	z},	{color.r, color.g, color.b, 1.0f} };

	indices[numTile * 6 + 0] = numTile * 4 + 0;
	indices[numTile * 6 + 1] = numTile * 4 + 1;
	indices[numTile * 6 + 2] = numTile * 4 + 2;
	indices[numTile * 6 + 3] = numTile * 4 + 2;
	indices[numTile * 6 + 4] = numTile * 4 + 3;
	indices[numTile * 6 + 5] = numTile * 4 + 0;
}

void Map::addTileToPath(glm::vec3 position, Tile::Direction direction)
{
	Tile& tile = tileMap.at(position);
	tile.setDirection(direction);

	pathTiles.emplace_back(&tileMap.at(position));
	path.addTile(&tile);
}

