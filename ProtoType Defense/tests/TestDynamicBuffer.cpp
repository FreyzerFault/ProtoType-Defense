#include "TestDynamicBuffer.h"
#include "GlobalParameters.h"
#include "imgui.h"
#include "TextureManager.h"

using namespace glm;
using namespace test;

test::TestDynamicBuffer::TestDynamicBuffer()
	: m_Position{ iniPosition[0], iniPosition[1], iniPosition[2] }, m_Size(iniSize), m_Rotation(iniRotation),
	m_QuadsX((int)sqrt(MAX_QUADS)), m_QuadsY((int)sqrt(MAX_QUADS)),
	m_VBO(4 * m_QuadsX*m_QuadsY * sizeof(Vertex)), // Vacio
	m_IBO(6 * m_QuadsX * m_QuadsY), // Vacio
	m_Shader(shaderPath),
	m_CurrentTexture(0),
	m_Proj(ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, -200.0f, 2000.0f)),
	m_View(lookAt(vec3(0.0f, 0.0f, 1000.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f))),
	m_Model(translate(mat4(1.0f), vec3(0, 0, 0)))
{
	// DYNAMIC BUFFER:
	const int numQuads = m_QuadsX * m_QuadsY;

	createBoard();
	m_VBO.setData(&m_BoardVertices, numQuads * 4 * sizeof(Vertex));
	m_IBO.setIndices(&m_BoardIndices, numQuads * 6);
	
	// LAYOUTs:

	VertexBufferLayout layout;
	layout.Push<float>(2); // Position
	layout.Push<float>(4); // Color
	layout.Push<float>(2); // TexCoord
	layout.Push<float>(1); // TexID

	m_VAO.addBuffer(m_VBO, layout);



	// TEXTURES:

	for (int i = 0; i < numTextures; i++)
	{
		m_Texture[i] = new Texture(textureFolderPath + std::to_string(i) + ".png"); // res/textures/{0,1,...}.png
	}

	m_VAO.Unbind();
	m_IBO.Unbind();
	m_VBO.Unbind();
}

test::TestDynamicBuffer::~TestDynamicBuffer() = default;

void test::TestDynamicBuffer::reset()
{
	m_Position[0] = iniPosition[0];
	m_Position[1] = iniPosition[1];
	m_Position[2] = iniPosition[2];
	m_Size = iniSize;
	m_Rotation = iniRotation;
	m_QuadsX = m_QuadsY = (int)sqrt(MAX_QUADS);
}

void test::TestDynamicBuffer::onUpdate(DeltaTime deltaTime)
{
	createBoard();
	m_VBO.Bind();
	m_IBO.Bind();
	m_VBO.updateData(&m_BoardVertices, m_QuadsX* m_QuadsY * 4 * sizeof(Vertex));
	m_IBO.updateIndices(&m_BoardIndices, m_QuadsX* m_QuadsY * 6);
	m_VBO.Unbind();
	m_IBO.Unbind();
}

void test::TestDynamicBuffer::onRender()
{
	Renderer::setClearColor();
	Renderer::clear();

	m_Shader.Bind();

	int texIndices[numTextures];
	for (int i = 0; i < numTextures; i++)
	{
		m_Texture[i]->Bind();
		texIndices[i] = i;
	}
	m_Texture[m_CurrentTexture]->Bind();
	m_Texture[(m_CurrentTexture+5) % numTextures]->Bind();
	m_Shader.setUniform1iv("u_Texture", numTextures, texIndices[0]);


	m_Model = translate(mat4(1.0f), vec3(m_Position[0], m_Position[1], m_Position[2]));
	m_Model = rotate(m_Model, m_Rotation * PI / 180, vec3(0, 0, 1));
	m_Model = scale(m_Model, vec3(m_Size, m_Size, 0));
	const mat4 mvp = m_Proj * m_View * m_Model; // MVP

	m_Shader.setUniformMat4f("u_MVP", mvp);


	Renderer::draw(m_VAO, m_IBO, m_Shader);
}

void test::TestDynamicBuffer::onImGuiRender()
{
	ImGui::SliderFloat("X", &m_Position[0], 0.0f, 1080.0f);
	ImGui::SliderFloat("Y", &m_Position[1], 0.0f, 720.0f);
	ImGui::SliderFloat("Z", &m_Position[2], -1000.0f, 1000.0f);
	ImGui::SliderFloat("Rotation", &m_Rotation, -360, 360);
	ImGui::SliderFloat("Scale", &m_Size, 0.0f, 10.0f);

	ImGui::SliderInt("NumQuadsX", &m_QuadsX, 4, 64);
	ImGui::SliderInt("NumQuadsY", &m_QuadsY, 4, 64);

	if (ImGui::Button("Reset")) reset();
}




TestDynamicBuffer::Vertex* TestDynamicBuffer::createQuad(
	Vertex* target, const float x, const float y, const float size, const float texIndex)
{
	*target = {{x,			y},			{tileColor[0], tileColor[1], tileColor[2], 1.0f}, {0.0f, 1.0f}, texIndex };
	target++;							
	*target = {{x + size,	y},			{tileColor[0], tileColor[1], tileColor[2], 1.0f}, {1.0f, 1.0f}, texIndex };
	target++;
	*target = {{x + size,	y + size},	{tileColor[0], tileColor[1], tileColor[2], 1.0f}, {1.0f, 0.0f}, texIndex };
	target++;
	*target = {{x,			y + size},	{tileColor[0], tileColor[1], tileColor[2], 1.0f}, {0.0f, 0.0f}, texIndex };
	target++;

	return target;
}

void test::TestDynamicBuffer::createBoard()
{
	uint32_t offsetIndex = 0;
	uint32_t offsetQuad = 0;
	for (int i = 0; i < m_QuadsX; i++)
		for (int j = 0; j < m_QuadsY; j++)
		{
			createQuad(&m_BoardVertices[offsetQuad], // target buffer quad
				(float)i * tileSize + 1, (float)j * tileSize + 1,
				tileSize - 2, (float)((i + j) % 2)); // ID de Textura intercalada (i+j)%2, -1 = solo color

			m_BoardIndices[offsetIndex + 0] = offsetQuad + 0;
			m_BoardIndices[offsetIndex + 1] = offsetQuad + 1;
			m_BoardIndices[offsetIndex + 2] = offsetQuad + 2;
			m_BoardIndices[offsetIndex + 3] = offsetQuad + 2;
			m_BoardIndices[offsetIndex + 4] = offsetQuad + 3;
			m_BoardIndices[offsetIndex + 5] = offsetQuad + 0;
			offsetIndex += 6;
			offsetQuad += 4;
		}
}