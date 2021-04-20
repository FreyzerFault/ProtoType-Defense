#include "TestSendingWaves.h"
#include "imgui.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "GlobalParameters.h"

using namespace test;

TestSendingWaves::TestSendingWaves()
	: m_View(glm::lookAt(glm::vec3(0.0f, 0.0f, 1000.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))),
	m_Model(glm::mat4(1.0f))
{
}

TestSendingWaves::~TestSendingWaves() = default;

void TestSendingWaves::reset()
{

}

void TestSendingWaves::onUpdate(DeltaTime deltaTime)
{
	if (!gameController.isActive()) gameController.startGame();
	
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
	
	// OTHER TIMERS
	shootTimer += deltaTime;
	enemyTimer += deltaTime;
	if (enemyTimer >= 1 / gameController.getRound().getWave().getFrecuency()) // [Speed] disparos / segundo
	{
		gameController.sendEnemy();
		enemyTimer -= 1 / gameController.getRound().getWave().getFrecuency();
		std::cout << "Sending Enemy" << std::endl;
	}
	
	// EACH FRAME CALCULATIONS
	gameController.getPath().moveEnemies(deltaTime);
	
}

void TestSendingWaves::onRender()
{
	Renderer::setClearColor();
	Renderer::clear();

	const glm::mat4 mvp = m_Proj * m_View * m_Model;

	gameController.render(mvp);
}

void TestSendingWaves::onImGuiRender()
{
	// GUI Buttons

	if (ImGui::Button("Reset")) reset();
}
