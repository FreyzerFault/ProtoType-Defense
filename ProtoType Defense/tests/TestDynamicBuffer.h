#pragma once

#include "Test.h"
#include "Renderer.h"
#include "Texture.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"


static float iniPosition[]{ // Esquina Inf Izq
	0.0f, 0.0f, 0.0f
};
static float iniSize = 1.0f;
static float iniRotation = 0;

static float tileSize = 16;
static float tileColor[3]{ 0.1f, 0.1f, 0.3f };

static std::string shaderPath = "res/shaders/Basic.shader";

static const int numTextures = 2;

static const unsigned int MAX_QUADS = 4096;


namespace test {

	class TestDynamicBuffer final : public Test
	{
		struct Vertex {
			float position[2];
			float color[4];
			float texCoords[2];
			float texIndex;
		};
		static const int numTextures = 10;

	private:
		float m_Position[3];
		float m_Size;
		float m_Rotation;
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
		unsigned int m_BoardIndices[MAX_QUADS * 6];

	public:
		TestDynamicBuffer();
		~TestDynamicBuffer() override;

		void reset() override;

		void onUpdate(DeltaTime deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;


		static Vertex* createQuad(Vertex* target, float x, float y, float size, float texIndex);

		void createBoard();

	};

}

