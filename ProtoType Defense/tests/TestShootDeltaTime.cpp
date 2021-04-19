#include "TestShootDeltaTime.h"

#include "imgui.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "GlobalParameters.h"

#define shader shaderManager.getShader()

using namespace glm;

using namespace test;

static float shootTimer = 0;
static int frames = 0;
static float fpsTimer = 0;
static int fpsCounter = 0;
static int fps = 60;

TestShootDeltaTime::TestShootDeltaTime()
	: m_View(glm::lookAt(glm::vec3(0.0f, 0.0f, 1000.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))),
	m_Model(glm::mat4(1.0f)),
	tower(0, new Platform(vec3(500.0f, 300.0f, 0.0f))),
	enemy(vec3(200, 100, 0), 10)
{
	// SHADERS
	shaderManager.add("Basic");
	shaderManager.add("NoTexture");
	
	// TEXTURAS
	shaderManager.Bind("Basic");

	for (int i = 0; i < numTextures; i++)
	{
		textureManager.add(std::to_string(i), i);
		std::cout << "Added texture " << textureManager.getTextureName(i) << " to Slot " << i << std::endl;
	}
	for (int i = 0; i < numTextures; i++)
	{
		textureManager.Bind(std::to_string(i), i);
	}
	//shader.setUniform1iv("u_Texture", MAX_TEXTURE_SLOTS, *textureManager.getTexIndeces());
	shaderManager.setTextureSlots(32);
	
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
	frames++;
	shootTimer += deltaTime;
	
	if (shootTimer >= 1/tower.getSpd()) // [Speed] disparos / segundo
	{
		tower.shoot();
		shootTimer -= 1/tower.getSpd();
		frames = 0;

		tower.setSpd(atkSpd);
	}

}

void TestShootDeltaTime::onRender()
{
	Renderer::setClearColor();
	Renderer::clear();
	
	shaderManager.Bind("Basic");

	const glm::mat4 mvp = m_Proj * m_View * m_Model; // MVP

	const glm::mat4 towerMVP = mvp * tower.getSprite().getModelMatrix(); // Tower Model Matrix
	shader.setUniformMat4f("u_MVP", towerMVP);
	Renderer::draw(tower.getSprite(), shader);

	const glm::mat4 enemyMVP = mvp * enemy.getSprite().getModelMatrix();
	shader.setUniformMat4f("u_MVP", enemyMVP);
	Renderer::draw(enemy.getSprite(), shader);

	for (Projectile& projectile : tower.getProjectiles())
	{
		shaderManager.Bind("Basic");
		const glm::mat4 projectileMVP = mvp * projectile.getSprite().getModelMatrix();
		shader.setUniformMat4f("u_MVP", projectileMVP);
		Renderer::draw(projectile.getSprite(), shader);

		shaderManager.Bind("NoTexture");
		shader.setUniformMat4f("u_MVP", mvp * projectile.getHitbox().getModelMatrix());
		Renderer::draw(hbGrid.VAO, hbGrid.IBO, shader, GL_LINE_LOOP);
	}
	
	// Hitbox Grids
	shaderManager.Bind("NoTexture");
	const glm::mat4 hitboxMVP = mvp * enemy.getHitbox().getModelMatrix();
	shader.setUniformMat4f("u_MVP", hitboxMVP);
	Renderer::draw(hbGrid.VAO, hbGrid.IBO, shader, GL_LINE_LOOP);

}

void TestShootDeltaTime::onImGuiRender()
{
	ImGui::InputFloat("AtkSpd", &atkSpd, 0.1f, 1.0f, "%.1f");

	if (ImGui::Button("Reset")) reset();
}
