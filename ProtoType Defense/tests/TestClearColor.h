#pragma once

#include "Test.h"

namespace test {
	class TestClearColor final : public Test
	{
	private:
		glm::vec4 m_ClearColor;
		Renderer m_Renderer;
	public:
		TestClearColor();
		~TestClearColor() override;

		void onUpdate(DeltaTime deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	};
}

