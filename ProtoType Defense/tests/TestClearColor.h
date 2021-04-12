#pragma once

#include "Test.h"
#include "Renderer.h"

namespace test {
	class TestClearColor final : public Test
	{
	private:
		float m_ClearColor[4];
		Renderer m_Renderer;
	public:
		TestClearColor();
		~TestClearColor() override;

		void onUpdate(DeltaTime deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	};
}

