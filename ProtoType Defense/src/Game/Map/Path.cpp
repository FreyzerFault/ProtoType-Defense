#include "pch.h"
#include "Path.h"


#define right Tile::Direction::right
#define left Tile::Direction::left
#define up Tile::Direction::up
#define down Tile::Direction::down

using namespace glm;


Path::Path(Renderer* renderer)
	: renderer(renderer), firstTile(nullptr)
{
}

Path::Path(std::list<Tile*>& tileList, Renderer* renderer)
	: path(tileList), renderer(renderer), firstTile(*tileList.begin())
{
	for (Tile* tile : tileList)
		pathMap.insert_or_assign(tile->getPosition(), tile);
}

void Path::spawnEnemy(TypeEnemy type)
{
	std::string name = std::to_string((int)type);
	const vec2 texSize = renderer->getTextureManager().getSize(name);
	const float resolution = texSize.x / texSize.y;
	
	float max = 64.f;
	vec2 scale;
	if (texSize.x > texSize.y)
		scale = vec2(max, max * resolution);
	else
		scale = vec2(max * resolution, max);

	Enemy* newEnemy = new Enemy(*getFirstTile(), (int)type, scale);
	
	enemies.emplace_back(newEnemy);
	orderedEnemies.push_back(newEnemy);
}

void Path::addTile(Tile* tile)
{
	if (pathMap.find(tile->getPosition()) == pathMap.end())
	{
		path.push_back(tile);
		pathMap.insert_or_assign(tile->getPosition(), tile);
	}
}

float Path::getTileSize() const
{
	return (*path.begin())->getSize();
}

glm::vec2 Path::getStartingPosition() const
{
	// Enemy starts from left to right, up to down...
	const vec2 tileCenter(firstTile->getCenter());
	switch (firstTile->getDirection())
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
	const vec2 firstTilePosition(getFirstTile()->getPosition());

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

int Path::moveEnemies(float deltaTime)
{
	int enemiesEnded = 0;
	
	for (auto i = enemies.begin(); i != enemies.end(); ++i)
	{
		Enemy* enemy = *i;
		// An enemy could be on the path or wandering on it's own (Tile* == nullptr)
		if (enemy->getTile() != nullptr)
		{
			if (enemyOutOfTile(*enemy))
			{
				Tile* tile = getEnemyTile(*enemy);
				// Si no encuentra Tile es porque salio del camino, osea que termino y lo eliminamos
				if (tile == nullptr)
				{
					i = enemies.erase(i);
					orderedEnemies.pop_front();

					enemiesEnded++;
					
					if (i == enemies.end()) break; // Si continua el for, lo primero que hace es ++i antes de i != end(), por lo que da error
					continue;
				}
				enemy->setTile(tile);
			}
		}
		
		enemy->move(enemy->getSpeed() * deltaTime);
	}
	return enemiesEnded;
}


Enemy* Path::getEnemy(Priority prior, glm::vec2 center, float range)
{
	switch (prior)
	{
	case Priority::first:
		return getFirstEnemy(center, range);
	case Priority::last:
		return getLastEnemy(center, range);
	case Priority::strong:
		return getStrongEnemy(center, range);
	case Priority::weak:
		return getWeakEnemy(center, range);
	}

}

Enemy* Path::getFirstEnemy()
{
	return orderedEnemies.empty() ? nullptr : *orderedEnemies.begin();
}

Enemy* Path::getLastEnemy()
{
	return orderedEnemies.empty() ? nullptr : orderedEnemies.back();
}

Enemy* Path::getStrongEnemy()
{
	Enemy* strongEnemy = nullptr;
	for (Enemy* enemy : orderedEnemies) // If there are enemies with same Life, takes the FIRST one of the Path
	{
		if (strongEnemy == nullptr)
			strongEnemy = enemy;

		if (enemy->getLife() > strongEnemy->getLife())
			strongEnemy = enemy;
	}
	return strongEnemy;
}

Enemy* Path::getWeakEnemy()
{
	Enemy* weakEnemy = nullptr;
	for (Enemy* enemy : orderedEnemies) // If there are enemies with same Life, takes the FIRST one of the Path
	{
		if (weakEnemy == nullptr)
			weakEnemy = enemy;

		if (enemy->getLife() < weakEnemy->getLife())
			weakEnemy = enemy;
	}
	return weakEnemy;
}

Enemy* Path::getFirstEnemy(glm::vec2 center, float range)
{
	// Select the simple method if Range = 0
	if (range <= 0)
		return getFirstEnemy();
	
	// Sort the Enemy List if not sorted
	sortEnemies();

	// The first enemy in LIST is the first enemy in PATH
	auto it = orderedEnemies.begin();
	// Search for the first one inside RANGE 
	while (it != orderedEnemies.end())
	{
		Enemy& enemy = **it;
		vec2 enemySize = enemy.getSize2D();
		const float margin = enemySize.x < enemySize.y ? enemySize.x : enemySize.y; // Smallest size as enemy MARGIN

		if (distance(enemy.getPosition2D(), center) - margin < range) // If enters inside the range
			return &enemy;
		++it;
	}
	// If no enemy in range:
	return nullptr;
}

Enemy* Path::getLastEnemy(glm::vec2 center, float range)
{
	// Select the simple method if Range = 0
	if (range <= 0)
		return getLastEnemy();
	
	// Sort the Enemy List if not sorted
	sortEnemies();

	// The first enemy in LIST is the first enemy in PATH
	auto it = orderedEnemies.begin();
	// Search for the last one inside RANGE
	Enemy* last = nullptr;
	while (it != orderedEnemies.end())
	{
		Enemy& enemy = **it;
		vec2 enemySize = enemy.getSize2D();
		const float margin = enemySize.x < enemySize.y ? enemySize.x : enemySize.y; // Smallest size as enemy MARGIN

		if (distance(enemy.getPosition2D(), center) - margin < range) // If enters inside the range
			last = &enemy;
		++it;
	}
	// If no enemy in range returns nullptr
	return last;
}

Enemy* Path::getStrongEnemy(glm::vec2 center, float range)
{
	// Select the simple method if Range = 0
	if (range <= 0)
		return getStrongEnemy();

	// Sort the Enemy List if not sorted
	sortEnemies();

	// The first enemy in LIST is the first enemy in PATH
	auto it = orderedEnemies.begin();
	// Search for the strongest one inside RANGE
	Enemy* strong = nullptr;
	while (it != orderedEnemies.end())
	{
		if ((*it)->inRange(center, range)) // If enters inside the range
			if (strong == nullptr)
				strong = *it;
			else
				if ((*it)->getLife() > strong->getLife())
					strong = *it;
		++it;
	}
	// If no enemy in range returns nullptr
	return strong;
}

Enemy* Path::getWeakEnemy(glm::vec2 center, float range)
{
	// Select the simple method if Range = 0
	if (range <= 0)
		return getWeakEnemy();

	// Sort the Enemy List if not sorted
	sortEnemies();

	// The first enemy in LIST is the first enemy in PATH
	auto it = orderedEnemies.begin();
	// Search for the weakest one inside RANGE
	Enemy* weak = nullptr;
	while (it != orderedEnemies.end())
	{
		if ((*it)->inRange(center, range)) // If enters inside the range
			if (weak == nullptr)
				weak = *it;
			else
				if ((*it)->getLife() < weak->getLife())
					weak = *it;
		++it;
	}
	// If no enemy in range returns nullptr
	return weak;
}

void Path::sortEnemies()
{
	if (enemiesSorted())
		return;
	
	orderedEnemies.clear();
	
	for (Tile* tile : path) // Path is ordered
	{
		std::list<Enemy*> enemyBuffer; // Temporal buffer to sort Enemies in the same Tile
		for (Enemy* enemy : enemies)
		{
			// Ignore enemies out the Tile
			if (enemy->getTile() != tile)
				continue;

			// First enemy in Tile inserts automatically
			if (enemyBuffer.empty())
			{
				enemyBuffer.push_back(enemy);
				continue;
			}

			// For every enemy in the same Tile, insert sorted comparing to other enemies
			auto it = enemyBuffer.begin();
			while (it != enemyBuffer.end())
			{
				switch (tile->getDirection()) // Depending on the Tile Direction
				{
				case right:
					if (enemy->getPosition2D().x > (*it)->getPosition2D().x)
					{
						enemyBuffer.insert(it, enemy);
						it = enemyBuffer.end(); // When inserted -> End searching
						continue;
					}
					break;
				case left:
					if (enemy->getPosition2D().x < (*it)->getPosition2D().x)
					{
						enemyBuffer.insert(it, enemy);
						it = enemyBuffer.end();
						continue;
					}
					break;
				case up:
					if (enemy->getPosition2D().y > (*it)->getPosition2D().y)
					{
						enemyBuffer.insert(it, enemy);
						it = enemyBuffer.end();
						continue;
					}
					break;
				case down:
					if (enemy->getPosition2D().y < (*it)->getPosition2D().y)
					{
						enemyBuffer.insert(it, enemy);
						it = enemyBuffer.end();
						continue;
					}
					break;
				}
				++it;
				
				// If enemy is the last one in Tile push at the end of buffer
				enemyBuffer.push_back(enemy);
			}
		}
		
		// Pass the buffer to the LIST of ordered enemies (First Tile is the last)
		orderedEnemies.insert(orderedEnemies.begin(), enemyBuffer.begin(), enemyBuffer.end());
		enemyBuffer.clear();
	}
}

bool Path::enemiesSorted()
{
	auto it = orderedEnemies.begin();
	while(it != orderedEnemies.end())
	{
		const auto itAux = it;
		++it;
		if (it != orderedEnemies.end() && enemyGoesFirst(**it, **itAux))
			return false;
	}
	return true;
}

bool Path::enemyGoesFirst(Enemy& a, Enemy& b)
{
	Tile* tilea = a.getTile();
	Tile* tileb = b.getTile();

	// If not the same Tile:
	if (tilea != tileb)
	{
		for (Tile* tile : path) // From last to First
		{
			if (tile == tilea) // A have the last Tile
				return false;
			if (tile == tileb) // A have the first Tile
				return true;
		}
	}

	// If SAME TILE:
	Tile* tile = tilea;
	
	bool goesFirst;
	
	switch (tile->getDirection()) // Depending on the Tile Direction
	{
		case right:
			goesFirst = a.getPosition2D().x > b.getPosition2D().x;
			break;
		case left:
			goesFirst = a.getPosition2D().x < b.getPosition2D().x;
			break;
		case up:
			goesFirst = a.getPosition2D().y > b.getPosition2D().y;
			break;
		case down:
			goesFirst = a.getPosition2D().y < b.getPosition2D().y;
			break;
		default:
			goesFirst = true;
			std::cout << "!!! ERROR !!! in enemyGoesFirst(), DEFAULT switch triggered" << std::endl;
	}

	return goesFirst;
}

int Path::deleteEnemy(Enemy* enemy)
{
	int reward = enemy->getReward();
	
	auto it = enemies.begin();
	while(it != enemies.end())
	{
		if (enemy == *it)
			it = enemies.erase(it);
		else
			++it;
	}
	it = orderedEnemies.begin();
	while (it != orderedEnemies.end())
	{
		if (enemy == *it)
		{
			delete *it;
			it = orderedEnemies.erase(it);
		}
		else
			++it;
	}

	return reward;
}
