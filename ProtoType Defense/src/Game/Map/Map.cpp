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
	: dimension(dimension), tileSize(64)
{
	vertices = new Vertex[dimension.x * dimension.y * 4];
	indices = new uint32_t[dimension.x * dimension.y * 6];
	
	for (int i = 0; i < dimension.y; i++)
	{
		for (int j = 0; j < dimension.x; j++)
		{
			vec3 position(j * tileSize, i * tileSize, 0.0f);
			tileMap.try_emplace(position, position, tileSize);

			// PATH
			if (i == round(dimension.y / 2) && j < round(dimension.x / 2))
			{
				addTileToPath(position, right);
				if (j == 0)
					path.setFirstTile(&tileMap.at(vec2(position)));

				addTileVertexData(j, i, position, colorPath);
			}
			else if (j == round(dimension.x / 2) && i <= round(dimension.y / 2) && i > round(dimension.y / 4))
			{
				addTileToPath(position, down);

				addTileVertexData(j, i, position, colorPath);
			}
			else if (i == round(dimension.y / 4) && j >= round(dimension.x / 2))
			{
				addTileToPath(position, right);

				addTileVertexData(j, i, position, colorPath);
			}
			else
				// Platforms
				if (i == round(dimension.y / 2) + 1)
				{	// Platforms above the path
					platforms.emplace_back(vec3(position.x, position.y + tileSize, 0.0f));

					addTileVertexData(j, i, position, colorPlatform);
				}
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

void Map::render(Renderer& renderer)
{
	renderer.draw(VAO, IBO, "NoTexture");
}

void Map::addTileVertexData(int tileX, int tileY, vec2 position, vec3 color) const
{
	// Index of the tile
	const uint32_t numTile = tileY * dimension.x + tileX;

	const float quadSize = tileSize - 1;

	vertices[numTile * 4 + 0] = { {position.x,				position.y,				0.0f},	{color.r, color.g, color.b, 1.0f} };
	color += 0.03f;
	vertices[numTile * 4 + 1] = { {position.x + quadSize,	position.y,				0.0f},	{color.r, color.g, color.b, 1.0f} };
	vertices[numTile * 4 + 2] = { {position.x + quadSize,	position.y + quadSize,	0.0f},	{color.r, color.g, color.b, 1.0f} };
	vertices[numTile * 4 + 3] = { {position.x,				position.y + quadSize,	0.0f},	{color.r, color.g, color.b, 1.0f} };

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
