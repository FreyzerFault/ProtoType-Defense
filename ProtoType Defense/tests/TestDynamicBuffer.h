#pragma once
#include "pch.h"

#include "Test.h"

#include "Renderer.h"

static GLfloat iniPosition[]{ // Esquina Inf Izq
	0.0f, 0.0f, 0.0f
};
static GLfloat iniSize = 1.0f;
static GLfloat iniRotation = 0;

static GLfloat tileSize = 16;
static GLfloat tileColor[3]{ 0.1f, 0.1f, 0.3f };

static std::string shaderPath = "res/shaders/Basic.shader";

static const int numTextures = 2;

static const GLuint MAX_QUADS = 4096;


namespace test {

	class TestDynamicBuffer final : public Test
	{
		struct Vertex {
			GLfloat position[2];
			GLfloat color[4];
			GLfloat texCoords[2];
			GLfloat texIndex;
		};
		static const int numTextures = 10;

	private:
		GLfloat m_Position[3];
		GLfloat m_Size;
		GLfloat m_Rotation;
		int m_QuadsX;
		int m_QuadsY;

		VertexArray m_VAO;
		VertexBuffer m_VBO;
		IndexBuffer m_IBO;
		Shader m_Shader;
		Texture* m_Texture[numTextures];
		Renderer m_Renderer;
		int m_CurrentTexture;

		glm::mat4 m_Proj;
		glm::mat4 m_View;
		glm::mat4 m_Model;

		Vertex m_BoardVertices[MAX_QUADS * 4];
		GLuint m_BoardIndices[MAX_QUADS * 6];

	public:
		TestDynamicBuffer();
		~TestDynamicBuffer() override;

		void reset() override;

		void onUpdate(DeltaTime deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;


		static Vertex* createQuad(Vertex* target, GLfloat x, GLfloat y, GLfloat size, GLfloat texIndex);

		void createBoard();

	};

}

