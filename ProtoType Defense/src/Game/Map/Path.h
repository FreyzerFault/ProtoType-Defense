#pragma once
#include <map>

#include "Tile.h"
#include "Objects/Enemy.h"


class Path
{
public:
	Path();
	Path(std::list<Tile*>& tileList);

	void spawnEnemy(TypeEnemy type);

	const std::list<Enemy>& getEnemyList() const { return enemies; }

	Enemy& getFirstEnemy() const;
	Enemy& getLastEnemy() const;
	Enemy& getStrongEnemy() const;
	Enemy& getWeakEnemy() const;

	float getTileSize() const;
	void moveEnemies(float deltaTime);

private:
	std::list<Tile*> path;
	std::list<Enemy> enemies;

	glm::vec3 startingPoint;
};

