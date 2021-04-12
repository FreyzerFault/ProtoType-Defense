#include "TestThreads.h"
#include "imgui.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "GlobalParameters.h"

using namespace test;


static std::string shaderPath = shaderFolderPath + "Basic.shader";

TestTemplate::TestTemplate()
	: m_Shader(shaderPath),
	m_Proj(glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, -200.0f, 2000.0f)),
	m_View(glm::lookAt(glm::vec3(0.0f, 0.0f, 1000.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))),
	m_Model(glm::mat4(1.0f))
{
	// TEXTURAS
	for (int i = 0; i < numTextures; i++)
	{
		m_Texture[i] = new Texture(textureFolderPath + std::to_string(i) + ".png");
		m_TexIndices[i] = i;
	}
}

TestTemplate::~TestTemplate() = default;

void TestTemplate::reset()
{

}

void TestTemplate::onUpdate(DeltaTime deltaTime)
{

}

void TestTemplate::onRender()
{
	Renderer::setClearColor();
	Renderer::clear();

	m_Shader.Bind();

	m_Shader.setUniform1iv("u_Texture", numTextures, m_TexIndices[0]);

	for (int i = 0; i < numTextures; i++)
	{
		m_Texture[i]->Bind(i);
	}

	glm::mat4 mvp = m_Proj * m_View * m_Model; // MVP
	m_Shader.setUniformMat4f("u_MVP", mvp);

	m_Renderer.draw(, m_Shader);
}

void TestTemplate::onImGuiRender()
{


	if (ImGui::Button("Reset")) reset();
}
