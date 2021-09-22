#pragma once
#include "pch.h"

#include "Renderer.h"


class HealthBar
{

public:
	HealthBar(glm::vec3 enemyPos, GLfloat height = 32.f, GLfloat length = 64.f);

	void decrease(GLfloat percentage);
	void move(GLfloat d, GLfloat yaw);
	void updateVertex();

	void setPosition(glm::vec3 pos) { barPos = pos; }

	GLfloat getLife() const { return life; }

	void reset();
	
	void draw(Renderer& renderer) const;

private:
	HitboxGrid::VertexSimple healthVertex[4];	// Life portion
	HitboxGrid::VertexSimple leftVertex[4];		// Empty life portion
	
	glm::vec3 barPos; // Bot-Left Corner
	GLfloat barLength;

	GLfloat life; // %
};

