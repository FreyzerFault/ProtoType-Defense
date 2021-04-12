#include "TestShootDeltaTime.h"

#include "imgui.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "GlobalParameters.h"

using namespace glm;

using namespace test;

static float shootTimer = 0;
static int frames = 0;
static float fpsTimer = 0;
static int fpsCounter = 0;
static int fps = 60;

static std::string shaderPath = shaderFolderPath + "Basic.shader";

TestShootDeltaTime::TestShootDeltaTime()
	: m_Shader(shaderPath),
	m_Proj(glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, -200.0f, 2000.0f)),
	m_View(glm::lookAt(glm::vec3(0.0f, 0.0f, 1000.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))),
	m_Model(glm::mat4(1.0f)),
	tower(0, new Platform(vec3(50.0f))),
	enemy(vec3(200), 2)
{
	// TEXTURAS
	for (int i = 0; i < numTextures; i++)
	{
		m_Texture[i] = new Texture(textureFolderPath + std::to_string(i) + ".png");
		m_TexIndices[i] = i;
	}
}

TestShootDeltaTime::~TestShootDeltaTime() = default;


void TestShootDeltaTime::reset()
{

}

void TestShootDeltaTime::onUpdate(DeltaTime deltaTime)
{

	// Move projectiles
	for (Projectile& projectile : tower.getProjectiles())
	{
		projectile.move(tower.getPrSpd() * deltaTime);
	}
	
	// Rotate tower towards aimed enemy
	tower.aimPredictive(enemy);
	
	// Enemy moves
	enemy.move(enemy.getSpeed() * deltaTime);
	
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

	m_Shader.Bind();

	m_Shader.setUniform1iv("u_Texture", numTextures, m_TexIndices[0]);

	for (int i = 0; i < numTextures; i++)
	{
		m_Texture[i]->Bind(i);
	}

	const glm::mat4 mvp = m_Proj * m_View * m_Model; // MVP

	const glm::mat4 towerMVP = mvp * tower.getSprite().getModelMatrix(); // Tower Model Matrix
	m_Shader.setUniformMat4f("u_MVP", towerMVP);
	m_Renderer.draw(tower.getSprite(), m_Shader);

	const glm::mat4 enemyMVP = mvp * enemy.getSprite().getModelMatrix();
	m_Shader.setUniformMat4f("u_MVP", enemyMVP);
	m_Renderer.draw(enemy.getSprite(), m_Shader);

	for (Projectile& projectile : tower.getProjectiles())
	{
		const glm::mat4 projectileMVP = mvp * projectile.getSprite().getModelMatrix();
		m_Shader.setUniformMat4f("u_MVP", projectileMVP);
		m_Renderer.draw(projectile.getSprite(), m_Shader);
	}
}

void TestShootDeltaTime::onImGuiRender()
{
	ImGui::InputFloat("AtkSpd", &atkSpd, 0.1f, 1.0f, "%.1f");

	if (ImGui::Button("Reset")) reset();
}
