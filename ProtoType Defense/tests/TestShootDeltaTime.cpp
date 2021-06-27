#include "pch.h"
#include "TestShootDeltaTime.h"

#include "GlobalParameters.h"
#include "Objects/Projectile.h"

#define shader shaderManager.getShader()

using namespace glm;

using namespace test;

TestShootDeltaTime::TestShootDeltaTime()
	: m_View(glm::lookAt(glm::vec3(0.0f, 0.0f, 1000.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))),
	m_Model(glm::mat4(1.0f)),
	tower(1, new Platform(vec3(500.0f, 300.0f, 0.0f), 64)),
	enemy(vec3(200, 100, 0), 2, 0, vec2(32, 64))
{
	tower.setRange(800);
}

TestShootDeltaTime::~TestShootDeltaTime() = default;


void TestShootDeltaTime::reset()
{
	atkSpd = Tower::baseAttackSpeed;
	pierce = Tower::baseProjectilePierce;
	enemy.setPosition(vec3(200, 100, 0));
	enemy.setYaw(0);
	tower.clearProjectiles();
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
		enemy.getHit(0);
		
		++i;
	}
	tower.moveProjectiles(deltaTime);
	
	// Rotate tower towards aimed enemy
	tower.aimPredictive(enemy);
	
	// Enemy moves
	if (enemy.getLife() <=0)
	{
		gameController.getAudioManager().playSound("coin");
		enemy.setPosition(vec3(200, 100, 0));
		enemy.setYaw(0);
		enemy.setLife(Enemy::baseLife);
	}
	
	enemy.move(enemy.getSpeed() * 5 * deltaTime);
	enemy.rotate(enemy.getSpeed() * PI/100 * deltaTime);
	
	tower.shoot(deltaTime);
}

void TestShootDeltaTime::onRender()
{
	Renderer::setClearColor();
	Renderer::clear();

	Renderer& renderer = gameController.getRenderer();
	
	// Scene MVP
	mat4 mvp(proj * m_View * m_Model);
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
	enemy.draw(renderer);
	enemy.drawHitbox(renderer);
}

void TestShootDeltaTime::onImGuiRender()
{
	ImGui::InputFloat("AtkSpd", &atkSpd, 0.1f, 1.0f, "%.1f");
	tower.setSpd(atkSpd);

	ImGui::InputInt("Pierce", &pierce, 1, 2);
	tower.setPierce(pierce);

	ImGui::Separator();

	ImGui::Text("Los proyectiles atraviesan al enemigo tantas veces como PIERCE tengan");
	ImGui::Text("Cuando golpean al enemigo, su capacidad de golpearlo en los siguientes frames se desactiva");
	ImGui::Text("Hasta que en uno de los frames deje de colisionar con el enemigo");
	ImGui::Text("Entonces podra volver a golpearlo");

	ImGui::Separator();
	
	ImGui::Text("Para hacerlo mas natural y que el enemigo sea golpeado con menos frecuencia");
	ImGui::Text("El proyectil tiene un limite de giro en cada frame muy pequenho para que sea progresivo");

	ImGui::Separator();

	if (ImGui::Button("Reset")) reset();
}
