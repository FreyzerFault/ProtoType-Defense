#pragma once
#include "pch.h"

#include "Test.h"
#include "AudioManager.h"
#include "GameController.h"

namespace test {

	class TestAudio : public test::Test
	{
	public:
		TestAudio();
		~TestAudio() override;

		void reset() override;

		void onUpdate(DeltaTime deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;

		static const int numTextures = 12;

	private:
		AudioManager audioManager;

		Renderer renderer;
		
		Platform* platform;
		Enemy* enemy;
	};
}
