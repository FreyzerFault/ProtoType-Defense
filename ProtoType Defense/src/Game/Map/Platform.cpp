#include "pch.h"
#include "Platform.h"
#include "Objects/Tower.h"


Platform::Platform(glm::vec3 position, GLfloat tileSize)
	: m_Position(position), m_Empty(true), m_Tower(nullptr), tileSize(tileSize)
{
}

Tower* Platform::placeTower(Tower& tower)
{
	if (m_Empty)
	{
		m_Tower = &tower;
		m_Empty = false;
		return m_Tower;
	}
	return nullptr;
}

Tower* Platform::placeTower(TypeTower type)
{
	if (!isEmpty())
		return nullptr;
	Tower* tower = new Tower((int)type, this);
	tower->setPierce(3);
	return placeTower(*tower);
}

int Platform::sellTower()
{
	if (isEmpty()) return 0;

	const int sellPrice = m_Tower->getCost() / 2;
	delete m_Tower;
	m_Tower = nullptr;
	m_Empty = true;
	return sellPrice;
}
