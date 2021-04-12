#pragma once

#include "Test.h"
#include "Renderer.h"
#include "Texture.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "Sprite.h"


namespace test {

	class TestDynamicSprites final : public Test
	{
		static const int numSprites = 1;
		static const int numTextures = 10;

	private:
		glm::vec3 m_Position;
		float m_Size;
		float m_Rotation;

		Shader m_Shader;
		Texture* m_Texture[numTextures];
		Renderer m_Renderer;

		glm::mat4 m_Proj;
		glm::mat4 m_View;
		glm::mat4 m_Model;

		int m_TexIndices[numTextures];
		int m_CurrentTexture;

		std::vector<Sprite> sprites;

	public:
		TestDynamicSprites();
		~TestDynamicSprites() override;

		void reset() override;

		void onUpdate(DeltaTime deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;

		static void addSprite(unsigned int textureID) = delete;
	};

}

