#pragma once
#include "pch.h"

#include "Test.h"
#include "Renderer.h"

namespace test {

	class TestBatchRendering final : public Test
	{
	private:
		float m_Position[3];
		float m_Size;
		float m_Rotation;

		VertexArray m_VAO;
		VertexBuffer m_VBO;
		IndexBuffer m_IBO;
		Shader m_Shader;
		Texture m_Texture[2];
		Renderer m_Renderer;

		glm::mat4 m_Proj;
		glm::mat4 m_View;
		glm::mat4 m_Model;

	public:
		TestBatchRendering();
		~TestBatchRendering() override;

		void reset() override;

		void onUpdate(DeltaTime deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;

	};

}

