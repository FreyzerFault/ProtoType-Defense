#pragma once
#include <map>
#include <vec2.hpp>


#include "Path.h"
#include "Tile.h"

struct cmpVec2 {
	// From top to bottom, if same y ==> from left to right
	bool operator()(const glm::vec2& a, const glm::vec2& b) const {
		return a.y == b.y ? a.x < b.x : a.y > b.y;
	}
};

class Map
{
public:
	Map();
	Map(glm::vec2 dimension);

	Path& getPath() const { return *path; };


private:
	glm::vec2 dimension;
	float tileSize;
	
	std::map<glm::vec2, Tile, cmpVec2> tileMap;

	std::list<Tile*> pathTiles;
	Path* path;
};

