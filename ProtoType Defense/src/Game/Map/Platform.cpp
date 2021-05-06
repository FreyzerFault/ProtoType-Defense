#include "Platform.h"
#include "Objects/Tower.h"

float Platform::size = 10.0f;


Platform::Platform(glm::vec3 position)
	: m_Position(position), m_Empty(true), m_Tower(nullptr)
{
}

bool Platform::placeTower(Tower& tower)
{
	if (m_Empty)
	{
		m_Tower = &tower;
		m_Empty = false;
		return true;
	}
	return false;
}
