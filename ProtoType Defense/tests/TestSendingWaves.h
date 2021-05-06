#pragma once
#include "Test.h"

namespace test {

	class TestSendingWaves : public test::Test
	{
	public:
		TestSendingWaves();
		virtual ~TestSendingWaves() override;

		void reset() override;
		
		void onUpdate(DeltaTime deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
		
		static const int numTextures = 12;

	private:
		
		glm::mat4 m_View;
		glm::mat4 m_Model;

		GameController gameController;
	};
}
