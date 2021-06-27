#pragma once
#include "pch.h"

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
	Map(Renderer* renderer);
	Map(glm::vec2 dimension, Renderer* renderer);

	
	// Tiles
	Platform* getPlatform(glm::vec2 pos);
	Tile* getTile(glm::vec2 pos);
	
	// Tile Corner Pos (down-left) (key of the maps)
	glm::vec2 getTilePos(glm::vec2 pos) const;
	float getTileSize() const { return tileSize; }
	
	Path& getPath() { return path; }
	std::map<glm::vec2, Platform, cmpVec2>& getPlatforms() { return platforms; }


	// Draw
	void setupRendering(Renderer& renderer);
	void draw(Renderer& renderer);
	void drawTowers(Renderer& renderer);
	void drawEnemies(Renderer& renderer);
	void drawTowerRange(Renderer& renderer);
	void drawHitboxes(Renderer& renderer);

private:

	glm::vec2 dimension;
	float tileSize;

	// EEDDs
	std::map<glm::vec2, Tile, cmpVec2> tileMap;

	std::list<Tile*> pathTiles;
	Path path;

	std::map<glm::vec2, Platform, cmpVec2> platforms;

	// Rendering
	Vertex* vertices;
	uint32_t* indices;
	
	VertexArray VAO;
	VertexBuffer VBO;
	VertexBufferLayout layout;
	IndexBuffer IBO;


	void addTileVertexData(int tileX, int tileY, glm::vec3 position, glm::vec3 color) const;
	void addTileToPath(glm::vec3 position, Tile::Direction direction);
};

