#include "pch.h"
#include "TestThreads.h"
#include "imgui.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "GlobalParameters.h"

using namespace test;

TestTemplate::TestTemplate()
	: m_View(glm::lookAt(glm::vec3(0.0f, 0.0f, 1000.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))),
	m_Model(glm::mat4(1.0f))
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

TestTemplate::~TestTemplate() = default;

void TestTemplate::reset()
{

}

void TestTemplate::onUpdate(DeltaTime deltaTime)
{
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

	// EACH FRAME CALCULATIONS


}

void TestTemplate::onRender()
{
	Renderer::setClearColor();
	Renderer::clear();

	shaderManager.Bind("Basic");

	const glm::mat4 mvp = m_Proj * m_View * m_Model; // MVP

	//Sprite DrawCalls


	// Other objects Drawcalls

}

void TestTemplate::onImGuiRender()
{
	// GUI Buttons

	if (ImGui::Button("Reset")) reset();
}
