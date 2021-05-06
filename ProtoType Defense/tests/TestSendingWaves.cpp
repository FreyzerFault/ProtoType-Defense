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
	gameController.startGame();
}

TestSendingWaves::~TestSendingWaves() = default;

void TestSendingWaves::reset()
{
	gameController.reset();
}


void TestSendingWaves::onUpdate(DeltaTime deltaTime)
{
	// OTHER TIMERS
	shootTimer += deltaTime; // TODO dentro de update()

	// EACH FRAME CALCULATIONS

	if (gameController.isActive())
		gameController.update(deltaTime);
	
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

	ImGui::LabelText("Game Speed", std::to_string(gameController.getSpeed()).c_str());
	
	if (ImGui::Button("<<")) gameController.fastForward(25);
	if (ImGui::Button("<")) gameController.fastForward(50);
	if (ImGui::Button(">")) gameController.fastForward(200);
	if (ImGui::Button(">>")) gameController.fastForward(400);

	
}
