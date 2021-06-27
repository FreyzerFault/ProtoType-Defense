#pragma once
#include "pch.h"

#include "GameController.h"
#include "InputManager.h"
#include "Test.h"

namespace test {

	class TestSendingWaves : public test::Test
	{
	public:
		TestSendingWaves();
		~TestSendingWaves() override;

		void reset() override;
		
		void onUpdate(DeltaTime deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
		
		static const int numTextures = 12;

	private:

		GameController gameController;

		bool viewPerspective = false;

		int selectedPrior = 0;

		InputManager inputManager;
	};
}
