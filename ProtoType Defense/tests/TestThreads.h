/*
* Crea torres que disparen concurrentemente con hilos
*/

#pragma once
#include "Test.h"
#include "Tower.h"


namespace test {

	class TestThreads final : public test::Test
	{
		static const int numTowers = 2;
		static const int numTextures = 10;

	private:

		Shader m_Shader;
		Texture* m_Texture[numTextures];
		Renderer m_Renderer;

		glm::mat4 m_Proj;
		glm::mat4 m_View;
		glm::mat4 m_Model;

		int m_TexIndices[numTextures];

		std::vector<Tower> m_Towers;

	public:
		TestThreads();
		virtual ~TestThreads() override;

		void reset() override;

		void onUpdate(DeltaTime deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	};
}

