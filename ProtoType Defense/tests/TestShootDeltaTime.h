#pragma once
#include "Renderer.h"
#include "Shader.h"
#include "Test.h"
#include "Texture.h"
#include "Tower.h"

namespace test {

	class TestShootDeltaTime : public Test
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

		Tower tower;

		float atkSpd = Tower::baseAttackSpeed;
	
	public:
		TestShootDeltaTime();
		virtual ~TestShootDeltaTime() override;

		void reset() override;

		void onUpdate(DeltaTime deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	};

}

