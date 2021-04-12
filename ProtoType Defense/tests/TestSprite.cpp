#include "TestSprite.h"
#include "GlobalParameters.h"
#include "imgui.h"

static float iniPosition[]{ // Esquina Inf Izq
	0.0f, 0.0f, 0.0f
};
static float iniSize = 10.0f;
static float iniRotation = 0;


static float spriteBoxVertex[] = {
		0.0f,			0.0f		  , 0.0f,0.0f,0.0f, 0.0f, 1.0f, 0.0f,
		0.0f + iniSize,	0.0f		  , 0.0f,0.0f,0.0f, 1.0f, 1.0f, 0.0f,
		0.0f + iniSize,	0.0f + iniSize, 0.0f,0.0f,0.0f, 1.0f, 0.0f, 0.0f,
		0.0f,			0.0f + iniSize, 0.0f,0.0f,0.0f, 0.0f, 0.0f, 0.0f,
};
static unsigned int spriteBoxIndices[] = {
		0, 1, 2,
		2, 3, 0,
};

static std::string shaderPath = shaderFolderPath + "Basic.shader";
static std::string texturePath = textureFolderPath + "DOGO.png";

test::TestSprite::TestSprite()
	: m_Position{ iniPosition[0], iniPosition[1], iniPosition[2] }, m_Size(iniSize), m_Rotation(iniRotation),
	m_Shader(shaderPath), m_Texture(texturePath),
	m_VBO(spriteBoxVertex, 4 * 4 * sizeof(float)),
	m_IBO(spriteBoxIndices, 6),
	m_Proj(glm::ortho(-50.0f, 0.50f, -50.0f, 50.0f, -1.0f, 1.0f)),
	m_View(translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
	m_Model(translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
{

	// LAYOUTs:

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(3);
	layout.Push<float>(2);
	layout.Push<float>(1);

	m_VAO.addBuffer(m_VBO, layout);


	m_VAO.Unbind();
	m_IBO.Unbind();
	m_VBO.Unbind();
	m_Shader.Unbind();
}

test::TestSprite::~TestSprite()
{

}

void test::TestSprite::reset()
{
	m_Position[0] = iniPosition[0];
	m_Position[1] = iniPosition[1];
	m_Position[2] = iniPosition[2];
	m_Size = iniSize;
	m_Rotation = iniRotation;
}

void test::TestSprite::onUpdate(DeltaTime deltaTime)
{

}

void test::TestSprite::onRender()
{

	m_Renderer.setClearColor();
	m_Renderer.clear();

	m_Shader.Bind();
	m_Texture.Bind(0);
	m_Shader.setTextureSlots(1);


	m_Model = translate(glm::mat4(1.0f), glm::vec3(m_Position[0], m_Position[1], m_Position[2]));
	m_Model = rotate(m_Model, rad(m_Rotation), glm::vec3(0, 0, 1));
	m_Model = scale(m_Model, glm::vec3(m_Size, m_Size, 0));
	glm::mat4 mvp = m_Proj * m_View * m_Model; // MVP

	m_Shader.setUniformMat4f("u_MVP", mvp);
	m_Renderer.draw(m_VAO, m_IBO, m_Shader);
}

void test::TestSprite::onImGuiRender()
{
	ImGui::SliderFloat("X", &m_Position[0], 0.0f, 1080.0f);
	ImGui::SliderFloat("Y", &m_Position[1], 0.0f, 720.0f);
	ImGui::SliderFloat("Rotation", &m_Rotation, -360, 360);
	ImGui::SliderFloat("Scale", &m_Size, 0.0f, 10.0f);

	if (ImGui::Button("Reset")) reset();
}
