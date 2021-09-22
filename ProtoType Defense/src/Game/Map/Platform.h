#pragma once
#include "pch.h"

enum class TypeTower;
class Tower;

class Platform
{
public:
	Platform(glm::vec3 position, GLfloat tileSize);
	Platform(const Platform& orig) = default;
	~Platform() = default;

	bool isEmpty() const { return m_Empty; }
	
	glm::vec3 getPosition() const { return m_Position; }
	glm::vec3 getCenter() const { return glm::vec3(glm::vec2(m_Position + tileSize / 2), m_Position.z); }


	// Tower
	Tower* placeTower(Tower& tower);
	Tower* placeTower(TypeTower type);
	
	int sellTower();

	Tower* getTower() const { return m_Tower; }


private:
	glm::vec3 m_Position;
	GLfloat tileSize;
	
	bool m_Empty;
	
	Tower* m_Tower;


};
