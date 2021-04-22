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

	const std::list<Enemy>& getEnemyList() const { return enemies; }

	float getTileSize() const;
	Tile& getFirstTile() const { return **path.begin(); }
	glm::vec2 getStartingPosition() const;
	Tile* getEnemyTile(const Enemy& enemy) const;
	
	void moveEnemies(float deltaTime);
	void removeEnemies() { enemies.clear(); }

	const Enemy& getFirstEnemy() const;
	const Enemy& getLastEnemy() const;
	const Enemy& getStrongEnemy() const;
	const Enemy& getWeakEnemy() const;

	bool noEnemiesLeft() const { return enemies.empty(); }
	

private:
	std::list<Tile*> path;
	std::unordered_map<glm::vec2, Tile*, KeyFuncs, KeyFuncs> pathMap;
	std::list<Enemy> enemies;
};

