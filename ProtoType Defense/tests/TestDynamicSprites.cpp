#include "TestDynamicSprites.h"
#include "GlobalParameters.h"
#include "imgui.h"

using namespace test;

// INITIAL PARAMETERS
static const float iniPosition[3]{ windowCenterX, windowCenterY, 0.0f };
static const float iniSize = 1.0f;
static const float iniRotation = 0.0f;

static std::string shaderPath = shaderFolderPath + "Basic.shader";


TestDynamicSprites::TestDynamicSprites()
	: m_Position(windowCenterX, windowCenterY, 0.0f),
	m_Size(iniSize), m_Rotation(iniRotation),
	m_Shader(shaderPath),
	//m_Proj(glm::perspective(45.0f, windowWidth / windowHeight, 1.0f, 2000.0f)),
	m_Proj(glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, -200.0f, 2000.0f)),
	//m_View(translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
	m_View(glm::lookAt(glm::vec3(0.0f, 0.0f, 1000.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))),
	m_Model(glm::mat4(1.0f)),
	m_CurrentTexture(0)
{
	// TEXTURA
	for (int i = 0; i < numTextures; i++)
	{
		m_Texture[i] = new Texture(textureFolderPath + std::to_string(i) + ".png");
		m_TexIndices[i] = i;
	}

	sprites.emplace_back(Sprite());

	m_Shader.Unbind();
}

TestDynamicSprites::~TestDynamicSprites() = default;

void TestDynamicSprites::reset()
{
	m_Position[0] = iniPosition[0];
	m_Position[1] = iniPosition[1];
	m_Position[2] = iniPosition[2];
	m_Size = iniSize;
	m_Rotation = iniRotation;
	sprites.clear();

	sprites.emplace_back(Sprite());
}

void TestDynamicSprites::onUpdate(DeltaTime deltaTime)
{
	sprites.at(0).setTransformation(m_Position, m_Size, m_Rotation);
}

void TestDynamicSprites::onRender()
{
	m_Renderer.setClearColor();
	m_Renderer.clear();

	m_Shader.Bind();

	m_Shader.setUniform1iv("u_Texture", numTextures, m_TexIndices[0]);

	for (int i = 0; i < numTextures; i++)
	{
		m_Texture[i]->Bind(i);
	}
	m_Texture[m_CurrentTexture]->Bind(0);

	const glm::mat4 mvp = m_Proj * m_View * sprites.at(0).getModelMatrix(); // MVP

	m_Shader.setUniformMat4f("u_MVP", mvp);
	m_Renderer.draw(sprites.at(0), m_Shader);
}

void TestDynamicSprites::onImGuiRender()
{
	ImGui::SliderFloat("X", &m_Position[0], 0.0f, 1080.0f);
	ImGui::SliderFloat("Y", &m_Position[1], 0.0f, 720.0f);
	ImGui::SliderFloat("Z", &m_Position[2], -1000.0f, 1000.0f);
	ImGui::SliderFloat("Rotation", &m_Rotation, -360, 360);
	ImGui::SliderFloat("Scale", &m_Size, 0.0f, 200.0f);

	ImGui::InputInt("Texture ID", &m_CurrentTexture);
	if (m_CurrentTexture < 0) m_CurrentTexture = 0;
	if (m_CurrentTexture >= numTextures) m_CurrentTexture = numTextures-1;

	if (ImGui::Button("Reset")) reset();
}