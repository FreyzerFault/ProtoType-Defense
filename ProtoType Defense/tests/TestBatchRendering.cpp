#include "pch.h"
#include "TestBatchRendering.h"

#include "GlobalParameters.h"
#include "ShaderManager.h"
#include "TextureManager.h"


static float iniPosition[]{ // Esquina Inf Izq
	windowCenterX, windowCenterY, 0.0f
};
static float iniSize = 200.0f;
static float iniRotation = 0;

static float spriteBoxVertex[] = {
		0.0f		,	0.0f		  ,		0.0f, 1.0f,		0.0f,
		0.0f + iniSize,	0.0f		  ,		1.0f, 1.0f,		0.0f,
		0.0f + iniSize,	0.0f + iniSize,		1.0f, 0.0f,		0.0f,
		0.0f		,	0.0f + iniSize,		0.0f, 0.0f,		0.0f,

		200.0f,				0.0f,				0.0f, 1.0f,		1.0f,
		200.0f + iniSize,	0.0f,				1.0f, 1.0f,		1.0f,
		200.0f + iniSize,	0.0f + iniSize,		1.0f, 0.0f,		1.0f,
		200.0f,				0.0f + iniSize,		0.0f, 0.0f,		1.0f,
};
static uint32_t spriteBoxIndices[] = {
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,
};

static std::string shaderPath = shaderFolderPath + "Basic.shader";
static std::string texturePath1 = textureFolderPath + "DOGO.png";
static std::string texturePath2 = textureFolderPath + "Foto de perfil mamadisima png.png";


test::TestBatchRendering::TestBatchRendering()
	: m_Position{ iniPosition[0], iniPosition[1], iniPosition[2] }, m_Size(iniSize), m_Rotation(iniRotation),
	m_VBO(spriteBoxVertex, 2 * 4*5 * sizeof(float)), m_IBO(spriteBoxIndices, 2 * 6),
	m_Shader(shaderPath),
	m_Texture{Texture(texturePath1), Texture(texturePath2)},
	//m_Proj(glm::perspective(45.0f, windowWidth / windowHeight, 1.0f, 2000.0f)),
	m_Proj(glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, -200.0f, 2000.0f)),
	//m_View(translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
	m_View(glm::lookAt(glm::vec3(0.0f, 0.0f, 1000.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))),
	m_Model(translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
{
	// LAYOUTs:

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	layout.Push<float>(1);

	m_VAO.addBuffer(m_VBO, layout);


	m_VAO.Unbind();
	m_IBO.Unbind();
	m_VBO.Unbind();
}

test::TestBatchRendering::~TestBatchRendering() = default;

void test::TestBatchRendering::reset()
{
	m_Position[0] = iniPosition[0];
	m_Position[1] = iniPosition[1];
	m_Position[2] = iniPosition[2];
	m_Size = iniSize;
	m_Rotation = iniRotation;
}

void test::TestBatchRendering::onUpdate(DeltaTime deltaTime)
{

}

void test::TestBatchRendering::onRender()
{
	Renderer::setClearColor();
	Renderer::clear();

	m_Shader.Bind();
	m_Texture[0].Bind();
	m_Texture[1].Bind();
	int texIndices[2] = {0, 1};
	m_Shader.setUniform1iv("u_Texture", 2, texIndices[0]);


	m_Model = translate(glm::mat4(1.0f), glm::vec3(m_Position[0], m_Position[1], m_Position[2]));
	m_Model = rotate(m_Model, rad(m_Rotation), glm::vec3(0, 0, 1));
	m_Model = scale(m_Model, glm::vec3(m_Size, m_Size, 0));
	const glm::mat4 mvp = m_Proj * m_View * m_Model; // MVP
	
	m_Renderer.draw(m_VAO, m_IBO, "Basic", mvp);
}

void test::TestBatchRendering::onImGuiRender()
{
	ImGui::SliderFloat("X", &m_Position[0], 0.0f, 1080.0f);
	ImGui::SliderFloat("Y", &m_Position[1], 0.0f, 720.0f);
	ImGui::SliderFloat("Z", &m_Position[2], -1000.0f, 1000.0f);
	ImGui::SliderFloat("Rotation", &m_Rotation, -360, 360);
	ImGui::SliderFloat("Scale", &m_Size, 0.0f, 10.0f);

	if (ImGui::Button("Reset")) reset();
}
