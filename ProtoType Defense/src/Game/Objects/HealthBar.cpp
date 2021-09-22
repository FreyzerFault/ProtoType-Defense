#include "pch.h"
#include "pch.h"

#include "HealthBar.h"

using namespace glm;

static GLfloat barThick = 8.f;

HealthBar::HealthBar(glm::vec3 enemyPos, GLfloat height, GLfloat length)
	: barPos(enemyPos.x - length / 2, enemyPos.y + height, enemyPos.z), barLength(length), life(100)
{
	// Start with Full bar
	vec4 healthColor(1.f, 0.f, 0.f, 1.f);
	
	updateVertex();
}

void HealthBar::decrease(GLfloat percentage)
{
	if (percentage > life) percentage = life;

	life -= percentage; // %
	updateVertex();
}


void HealthBar::move(GLfloat d, GLfloat yaw)
{
	barPos.x += d * cos(yaw);
	barPos.y += d * sin(yaw);

	updateVertex();
}

void HealthBar::updateVertex()
{
	healthVertex[0] = { {barPos.x, barPos.y, barPos.z},										{0.f, 1.f, 0.f, 1.f} };
	healthVertex[1] = { {barPos.x + barLength * life / 100, barPos.y, barPos.z},			{0.f, 1.f, 0.f, 1.f} };
	healthVertex[2] = { {barPos.x + barLength * life / 100, barPos.y + barThick, barPos.z},	{0.f, 1.f, 0.f, 1.f} };
	healthVertex[3] = { {barPos.x, barPos.y + barThick, barPos.z},							{0.f, 1.f, 0.f, 1.f} };

	leftVertex[0] = { {barPos.x + barLength * life / 100, barPos.y, barPos.z},				{1.f, 0.f, 0.f, 1.f} };
	leftVertex[1] = { {barPos.x + barLength, barPos.y, barPos.z},							{1.f, 0.f, 0.f, 1.f} };
	leftVertex[2] = { {barPos.x + barLength, barPos.y + barThick, barPos.z},				{1.f, 0.f, 0.f, 1.f} };
	leftVertex[3] = { {barPos.x + barLength * life / 100, barPos.y + barThick, barPos.z},	{1.f, 0.f, 0.f, 1.f} };
}

void HealthBar::reset()
{
	life = 100;
}

void HealthBar::draw(Renderer& renderer) const
{
	renderer.drawQuad<HitboxGrid::VertexSimple>(healthVertex, "NoTexture");
	renderer.drawQuad<HitboxGrid::VertexSimple>(leftVertex, "NoTexture");
}
