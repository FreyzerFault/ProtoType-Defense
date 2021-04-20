#pragma once
#include "Test.h"

namespace test {

	class TestShootDeltaTime : public Test
	{
	
	public:
		TestShootDeltaTime();
		virtual ~TestShootDeltaTime() override;

		void reset() override;

		void onUpdate(DeltaTime deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;

		static const int numTextures = 12;
	
	private:

		glm::mat4 m_View;
		glm::mat4 m_Model;

		Tower tower;

		Enemy enemy;

		float atkSpd = (float)Tower::baseAttackSpeed;

		GameController gameController;
	
	};

}

