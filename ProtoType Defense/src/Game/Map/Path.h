#pragma once
#include <unordered_map>


#include "GlobalParameters.h"
#include "Tile.h"
#include "Objects/Enemy.h"

struct KeyFuncs
{
	size_t operator()(const glm::vec2& k)const
	{
		return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
	}

	bool operator()(const glm::vec2& a, const glm::vec2& b)const
	{
		return a.x == b.x && a.y == b.y;
	}
};

class Path
{
public:
	Path();
	Path(std::list<Tile*>& tileList);

	void spawnEnemy(TypeEnemy type);

	std::list<Enemy>& getEnemyList() { return enemies; }

	void addTile(Tile* tile);

	Tile* getFirstTile() const { return firstTile; }
	void setFirstTile(Tile* tile) { firstTile = tile; }
	glm::vec2 getStartingPosition() const;
	
	float getTileSize() const;
	Tile* getEnemyTile(const Enemy& enemy) const;
	
	void moveEnemies(float deltaTime);
	void removeEnemies() { enemies.clear(); }

	Enemy& getFirstEnemy();
	Enemy& getLastEnemy();
	Enemy& getStrongEnemy();
	Enemy& getWeakEnemy();

	bool noEnemiesLeft() const { return enemies.empty(); }
	

private:
	std::list<Tile*> path;
	std::unordered_map<glm::vec2, Tile*, KeyFuncs, KeyFuncs> pathMap;
	std::list<Enemy> enemies;

	Tile* firstTile;
};

