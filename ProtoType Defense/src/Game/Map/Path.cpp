#include "Path.h"


#define right Tile::Direction::right
#define left Tile::Direction::left
#define up Tile::Direction::up
#define down Tile::Direction::down

using namespace glm;


Path::Path()
{
}

Path::Path(std::list<Tile*>& tileList)
	: path(tileList)
{
	for (Tile* tile : tileList)
		pathMap.insert_or_assign(tile->getPosition(), tile);
}

void Path::spawnEnemy(TypeEnemy type)
{
	enemies.emplace_back(getFirstTile());
}

float Path::getTileSize() const
{
	return (*path.begin())->getSize();
}

glm::vec2 Path::getStartingPosition() const
{
	// Enemy starts from left to right, up to down...
	const vec2 tileCenter((*path.begin())->getCenter());
	switch ((*path.begin())->getDirection())
	{
	case right:
		return vec2(tileCenter.x - getTileSize() / 2, tileCenter.y);
	case left:
		return vec2(tileCenter.x + getTileSize() / 2, tileCenter.y);
	case up:
		return vec2(tileCenter.x, tileCenter.y - getTileSize() / 2);
	case down:
		return vec2(tileCenter.x, tileCenter.y + getTileSize() / 2);
	}
	return tileCenter;
}

Tile* Path::getEnemyTile(const Enemy& enemy) const
{
	// Para normalizar la posicion del enemigo a la de las tiles, como el mapa no tiene por que estar cuadrado con 0,0
	//  podemos cuadrar el mapa colocando la primera tile en 0,0,
	//  normalizamos al tamaño de las tiles sacando nº de tile que ocupa,
	//  (* tileSize) para calcular la posicion de la Tile
	//   y volvemos a mover el mapa donde estaba

	const vec2 tileSize(getTileSize());
	const vec2 firstTilePosition(getFirstTile().getPosition());

	const vec2 relativePos(floor((enemy.getPosition2D() - firstTilePosition) / tileSize));
	const vec2 tilePos(relativePos * tileSize + firstTilePosition);

	auto it = pathMap.find(tilePos);
	if (it != pathMap.end())
		return it->second;
	return nullptr;
}

bool enemyOutOfTile(Enemy& enemy)
{
	const vec2 enemyPos(enemy.getPosition2D());
	const vec2 tilePos(enemy.getTile()->getPosition());
	const vec2 tileSize(enemy.getTile()->getSize());
	return
		enemyPos.x < tilePos.x ||
		enemyPos.x > tilePos.x + tileSize.x ||
		enemyPos.y < tilePos.y ||
		enemyPos.y > tilePos.y + tileSize.y;
}

void Path::moveEnemies(float deltaTime)
{
	for (auto i = enemies.begin(); i != enemies.end(); ++i)
	{
		Enemy& enemy = *i;
		// An enemy could be on the path or wandering on it's own (Tile* == nullptr)
		if (enemy.getTile() != nullptr)
		{
			if (enemyOutOfTile(enemy))
			{
				Tile* tile = getEnemyTile(enemy);
				// Si no encuentra Tile es porque salio del camino, osea que termino y lo eliminams
				if (tile == nullptr)
				{
					i = enemies.erase(i);
					if (i == enemies.end()) break; // Si continua el for, lo primero que hace es ++i antes de i != end(), por lo que da error
					continue;
				}
				enemy.setTile(tile);
			}
		}
		
		enemy.move(enemy.getSpeed() * deltaTime);
	}
}



const Enemy& Path::getFirstEnemy() const
{
	// 1º: Search for the last Tile with Enemies (List order)

	Tile* maxTile = *path.begin();
	int maxCount = 0;

	for (const Enemy& enemy : enemies)
	{
		// Contamos por cada enemigo como de lejos esta su Tile en la lista
		int tileCount = 0;
		for (Tile* tile : path)
		{
			if (tile == enemy.getTile()) // Encontro su Tile
			{
				if (tileCount > maxCount) // Esta mas lejos
				{
					maxCount = tileCount;
					maxTile = tile;
				}
				break;
			}
			tileCount++;
		}
	}

	// 2º: Compare with other enemies in the same Tile

	const Enemy* firstEnemy = nullptr;

	for (const Enemy& enemy : enemies)
	{
		if (enemy.getTile() == maxTile)
		{
			if (firstEnemy == nullptr)
			{
				firstEnemy = &enemy;
				continue;
			}
			switch (maxTile->getDirection())
			{
			case right:
				if (enemy.getPosition2D().x > firstEnemy->getPosition2D().x)
					firstEnemy = &enemy;
				break;
			case left:
				if (enemy.getPosition2D().x < firstEnemy->getPosition2D().x)
					firstEnemy = &enemy;
				break;
			case up:
				if (enemy.getPosition2D().y > firstEnemy->getPosition2D().y)
					firstEnemy = &enemy;
				break;
			case down:
				if (enemy.getPosition2D().y < firstEnemy->getPosition2D().y)
					firstEnemy = &enemy;
				break;
			}
		}
	}

	return *firstEnemy;
}

const Enemy& Path::getLastEnemy() const
{
	// 1º: Search for the first Tile with Enemies (List order)

	Tile* minTile = *path.begin();
	int minCount = (int)INFINITY;

	for (const Enemy& enemy : enemies)
	{
		// Contamos por cada enemigo como de lejos esta su Tile en la lista
		int tileCount = 0;
		for (Tile* tile : path)
		{
			if (tile == enemy.getTile()) // Encontro su Tile
			{
				if (tileCount < minCount) // Esta mas lejos
				{
					minCount = tileCount;
					minTile = tile;
				}
				break;
			}
			tileCount++;
		}
	}

	// 2º: Compare with other enemies in the same Tile

	const Enemy* lastEnemy = nullptr;

	for (const Enemy& enemy : enemies)
	{
		if (enemy.getTile() == minTile)
		{
			if (lastEnemy == nullptr)
			{
				lastEnemy = &enemy;
				continue;
			}
			switch (minTile->getDirection())
			{
			case right:
				if (enemy.getPosition2D().x < lastEnemy->getPosition2D().x)
					lastEnemy = &enemy;
				break;
			case left:
				if (enemy.getPosition2D().x > lastEnemy->getPosition2D().x)
					lastEnemy = &enemy;
				break;
			case up:
				if (enemy.getPosition2D().y < lastEnemy->getPosition2D().y)
					lastEnemy = &enemy;
				break;
			case down:
				if (enemy.getPosition2D().y > lastEnemy->getPosition2D().y)
					lastEnemy = &enemy;
				break;
			}
		}
	}

	return *lastEnemy;
}

const Enemy& Path::getStrongEnemy() const
{
	const Enemy* strongEnemy = nullptr;
	for (const Enemy& enemy : enemies)
	{
		if (strongEnemy == nullptr)
			strongEnemy = &enemy;

		if (enemy.getLife() > strongEnemy->getLife())
			strongEnemy = &enemy;
	}
	return *strongEnemy;
}

const Enemy& Path::getWeakEnemy() const
{
	const Enemy* weakEnemy = nullptr;
	for (const Enemy& enemy : enemies)
	{
		if (weakEnemy == nullptr)
			weakEnemy = &enemy;

		if (enemy.getLife() < weakEnemy->getLife())
			weakEnemy = &enemy;
	}
	return *weakEnemy;
}
