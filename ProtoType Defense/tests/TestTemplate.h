#pragma once
#include "Test.h"

namespace test {

	class TestTemplate : public test::Test
	{
		static const int numTextures = 10;

	private:

		Shader m_Shader;
		Renderer m_Renderer;
		Texture* m_Texture[numTextures];
		int m_TexIndices[numTextures];

		glm::mat4 m_Proj;
		glm::mat4 m_View;
		glm::mat4 m_Model;

	public:
		TestTemplate();
		virtual ~TestTemplate() override;

		void reset() override;

		void onUpdate(DeltaTime deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	};
}
