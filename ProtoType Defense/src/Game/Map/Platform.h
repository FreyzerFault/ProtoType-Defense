#pragma once
#ifndef Platform_H
#define Platform_H

#include "glm.hpp"

class Tower;


class Platform
{
public:
	Platform(glm::vec3 position);
	Platform(const Platform& orig) = default;
	~Platform() = default;

	glm::vec3 getPosition() const { return m_Position; };
	bool isEmpty() const { return m_Empty; }
	static float getSize() { return size; }
	Tower* getTower() const { return m_Tower; }

	bool placeTower(Tower& tower);

	static float size;

private:
	glm::vec3 m_Position;
	bool m_Empty;
	Tower* m_Tower;


};

#endif
