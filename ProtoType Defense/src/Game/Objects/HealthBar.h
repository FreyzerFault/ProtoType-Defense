#pragma once
#include "pch.h"

#include "Renderer.h"


class HealthBar
{

public:
	HealthBar(glm::vec3 enemyPos, float height = 32.f, float length = 64.f);

	void decrease(float percentage);
	void move(float d, float yaw);
	void updateVertex();

	void setPosition(glm::vec3 pos) { barPos = pos; }

	float getLife() const { return life; }

	void reset();
	
	void draw(Renderer& renderer) const;

private:
	HitboxGrid::VertexSimple healthVertex[4];	// Life portion
	HitboxGrid::VertexSimple leftVertex[4];		// Empty life portion
	
	glm::vec3 barPos; // Bot-Left Corner
	float barLength;

	float life; // %
};

