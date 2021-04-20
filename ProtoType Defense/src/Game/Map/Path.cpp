#include "Path.h"

using namespace glm;

Path::Path()
{
}

Path::Path(std::list<Tile*>& tileList)
	: path(tileList), startingPoint((*tileList.begin())->getPosition(), 1.0f)
{
}

void Path::spawnEnemy(TypeEnemy type)
{
	enemies.emplace_back(startingPoint);
}

Enemy& Path::getFirstEnemy() const
{
	// 1º: Search for the last Tile with Enemies
	
	Tile* maxTile = *path.begin();
	int maxCount = 0;
	
	for (const Enemy& enemy : enemies)
	{
		// floor(EnemyPos / TileSize) = NumTiles from beginning
		// NumTiles * TileSize = tilePos
		const vec2 relativePos(floor(enemy.getPosition2D().x / getTileSize()) * getTileSize(), floor(enemy.getPosition2D().y / getTileSize()) * getTileSize());
		int tileCount = 0;
		for (auto i = path.begin(); i != path.end(); ++i)
		{
			// Posicion del enemigo = Tile && es la tile mas lejana
			if ((*i)->getPosition() == relativePos && tileCount > maxCount)
			{
				maxCount = tileCount;
				maxTile = *i;
				break;
			}
			tileCount++;
		}
	}
	
	// 2º: Compare with other enemies in the same Tile
	
	std::vector<Enemy*> firstTileEnemies;
	
	for (auto enemy : enemies)
	{
		const vec2 relativePos(floor(enemy.getPosition2D().x / getTileSize()) * getTileSize(), floor(enemy.getPosition2D().y / getTileSize()) * getTileSize());
		if (relativePos == maxTile->getPosition())
		{
			firstTileEnemies.push_back(&enemy);
		}
	}

	// 3º: First one relatively to the direction of the pathTile TODO

	return *firstTileEnemies.front();
}

float Path::getTileSize() const
{
	return (*path.begin())->getSize();
}

void Path::moveEnemies(float deltaTime)
{
	for (Enemy& enemy : enemies)
		enemy.move(enemy.getSpeed() * 5 * deltaTime);
}
