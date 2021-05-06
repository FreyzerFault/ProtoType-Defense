#pragma once
#include <map>
#include <vec2.hpp>


#include "Path.h"
#include "Platform.h"
#include "Tile.h"

struct cmpVec2 {
	// From top to bottom, if same y ==> from left to right
	bool operator()(const glm::vec2& a, const glm::vec2& b) const {
		return a.y == b.y ? a.x < b.x : a.y > b.y;
	}
};

class Map
{
	struct Vertex {
		float position[3];
		float color[4];
	};
	struct QuadIndices{
		uint32_t index[6];
	};
	
public:
	Map();
	Map(glm::vec2 dimension);

	Path& getPath() { return path; }
	std::list<Platform>& getPlatforms() { return platforms; }

	void setupRendering(Renderer& renderer);
	
	void render(Renderer& renderer);

private:

	void addTileVertexData(int tileX, int tileY, glm::vec2 position, glm::vec3 color) const;
	
	void addTileToPath(glm::vec3 position, Tile::Direction direction);
	
	glm::vec2 dimension;
	float tileSize;
	
	std::map<glm::vec2, Tile, cmpVec2> tileMap;

	std::list<Tile*> pathTiles;
	Path path;

	std::list<Platform> platforms;
	
	Vertex* vertices;
	uint32_t* indices;
	
	VertexArray VAO;
	VertexBuffer VBO;
	VertexBufferLayout layout;
	IndexBuffer IBO;
};

