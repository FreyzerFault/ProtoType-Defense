#include "TestThreads.h"
#include "imgui.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "GlobalParameters.h"

#include <thread>

static std::string shaderPath = shaderFolderPath + "Basic.shader";

test::TestThreads::TestThreads()
	: m_Shader(shaderPath),
	m_Proj(glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, -200.0f, 2000.0f)),
	m_View(glm::lookAt(glm::vec3(0.0f, 0.0f, 1000.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))),
	m_Model(glm::mat4(1.0f))
{
	for (int i = 0; i < numTowers; i++)
	{
		m_Towers.push_back(Tower(i, new Platform(i * 100.0f, windowCenterY, 0.0f)));
	}

	// TEXTURAS
	for (int i = 0; i < numTextures; i++)
	{
		m_Texture[i] = new Texture(textureFolderPath + std::to_string(i) + ".png");
		m_TexIndices[i] = i;
	}
}

test::TestThreads::~TestThreads() = default;

void test::TestThreads::reset()
{
	m_Towers.clear();
	for (int i = 0; i < numTowers; i++)
	{
		m_Towers.emplace_back(Tower());
	}
}

void test::TestThreads::onUpdate(DeltaTime deltaTime)
{

}

void test::TestThreads::onRender()
{
	Renderer::setClearColor();
	Renderer::clear();

	m_Shader.Bind();

	m_Shader.setUniform1iv("u_Texture", numTextures, m_TexIndices[0]);

	for (int i = 0; i < numTextures; i++)
	{
		m_Texture[i]->Bind(i);
	}

	for (int i = 0; i < numTowers; i++)
	{
		glm::mat4 mvp = m_Proj * m_View * m_Towers.at(i).getSprite().getModelMatrix(); // MVP

		m_Shader.setUniformMat4f("u_MVP", mvp);
		m_Renderer.draw(m_Towers.at(i).getSprite(), m_Shader);
	}
}

void shoot(Tower* tower)
{
	tower->shoot();
}

void test::TestThreads::onImGuiRender()
{

	if (ImGui::Button("Shoot"))
	{
		std::vector<std::thread> threads;
		threads.reserve(numTowers);
		for (int i = 0; i < numTowers; i++)
		{	// Los argumentos del thread que se pasen por valor
			//y no por referencia necesitan std::ref()
			threads.emplace_back(std::thread(shoot, &m_Towers.at(i)));
		}
		for (int i = 0; i < numTowers; i++)
		{
			threads.at(i).join();
		}
	}


	if (ImGui::Button("Reset")) reset();
}
