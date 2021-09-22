#pragma once
#include "pch.h"

#include "GlobalParameters.h"
#include "Tile.h"
#include "Objects/Enemy.h"
#include "Objects/Tower.h"

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
	Path(Renderer* renderer = nullptr);
	Path(std::list<Tile*>& tileList, Renderer* renderer = nullptr);


	// Tiles
	void addTile(Tile* tile);

	Tile* getFirstTile() const { return firstTile; }
	Tile* getEnemyTile(const Enemy& enemy) const;
	GLfloat getTileSize() const;
	
	void setFirstTile(Tile* tile) { firstTile = tile; }
	glm::vec2 getStartingPosition() const;

	bool isPath(glm::vec2 position) { return pathMap.find(position) != pathMap.end(); }
	


	// Priority Searching
	Enemy* getEnemy(Priority prior, glm::vec2 center = glm::vec2(0.f), GLfloat range = 0); // Range is 0 when global range

	// Global Range
	Enemy* getFirstEnemy();
	Enemy* getLastEnemy();
	Enemy* getStrongEnemy();
	Enemy* getWeakEnemy();
	
	// Within range
	Enemy* getFirstEnemy(glm::vec2 center, GLfloat range);
	Enemy* getLastEnemy(glm::vec2 center, GLfloat range);
	Enemy* getStrongEnemy(glm::vec2 center, GLfloat range);
	Enemy* getWeakEnemy(glm::vec2 center, GLfloat range);


	// Enemies
	void spawnEnemy(TypeEnemy type);
	
	bool noEnemiesLeft() const { return enemies.empty(); }

	void sortEnemies();
	bool enemiesSorted();
	bool enemyGoesFirst(Enemy& a, Enemy& b); // Sort 2 enemies
	std::list<Enemy*>& getEnemyList() { return enemies; }

	int deleteEnemy(Enemy* enemy); // Return the reward when killed
	void clearEnemies() { enemies.clear(); }
	
	int moveEnemies(GLfloat deltaTime); // Return Nº enemies that reach the end of path to lower lives

private:
	std::list<Tile*> path;
	std::unordered_map<glm::vec2, Tile*, KeyFuncs, KeyFuncs> pathMap;
	
	std::list<Enemy*> enemies;
	std::list<Enemy*> orderedEnemies; // Used for searching first or last enemy to aim

	Tile* firstTile;

	
	Renderer* renderer; // Used to take the enemy texture sizes to spawn with the correct size
};

