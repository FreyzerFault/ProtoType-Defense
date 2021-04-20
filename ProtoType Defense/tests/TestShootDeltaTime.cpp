#include "TestShootDeltaTime.h"

#include "imgui.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "GlobalParameters.h"

#define shader shaderManager.getShader()

using namespace glm;

using namespace test;

TestShootDeltaTime::TestShootDeltaTime()
	: m_View(glm::lookAt(glm::vec3(0.0f, 0.0f, 1000.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))),
	m_Model(glm::mat4(1.0f)),
	tower(0, new Platform(vec3(500.0f, 300.0f, 0.0f))),
	enemy(vec3(200, 100, 0))
{
}

TestShootDeltaTime::~TestShootDeltaTime() = default;


void TestShootDeltaTime::reset()
{

}

void TestShootDeltaTime::onUpdate(DeltaTime deltaTime)
{
	// Move projectiles
	auto i = tower.getProjectiles().begin();
	while (i != tower.getProjectiles().end())
	{
		if (i->impact(enemy.getHitbox()))
		{
			enemy.getHit(tower.getDmg());
			
			if (i->getPierce() <= 0)
			{
				const std::list<Projectile>::iterator iErased = i;
				++i;
				tower.getProjectiles().erase(iErased);
			}
			continue;
		}
		i->move(tower.getPrSpd() * deltaTime);
		++i;
	}
	
	// Rotate tower towards aimed enemy
	tower.aimPredictive(enemy);
	
	// Enemy moves
	enemy.move(enemy.getSpeed() * 5 * deltaTime);
	enemy.rotate(enemy.getSpeed() * PI/200 * deltaTime);
	
	// FPS Timer
	fpsCounter++;
	fpsTimer += deltaTime;
	
	if (fpsTimer >= 1) // Every Sec
	{
		fps = fpsCounter;
		std::cout << fps << "fps" << std::endl;
		fpsTimer -= 1;
		fpsCounter = 0;
	}

	// Shooting Timer
	shootTimer += deltaTime;
	
	if (shootTimer >= 1/tower.getSpd()) // [Speed] disparos / segundo
	{
		tower.shoot();
		shootTimer -= 1/tower.getSpd();

		tower.setSpd(atkSpd);
	}

}

void TestShootDeltaTime::onRender()
{
	Renderer::setClearColor();
	Renderer::clear();

	Renderer& renderer = gameController.getRenderer();
	
	// Scene MVP
	mat4 mvp(m_Proj * m_View * m_Model);
	renderer.setMVP(mvp);

	// TILEMAP


	// TOWERS
	
	renderer.draw(tower.getSprite());

	// PROJECTILES
	for (Projectile& projectile : tower.getProjectiles())
	{
		renderer.draw(projectile.getSprite());
		renderer.draw(projectile.getHitbox());
	}

	// ENEMIES
	renderer.draw(enemy.getSprite());
	renderer.draw(enemy.getHitbox());
}

void TestShootDeltaTime::onImGuiRender()
{
	ImGui::InputFloat("AtkSpd", &atkSpd, 0.1f, 1.0f, "%.1f");

	if (ImGui::Button("Reset")) reset();
}
