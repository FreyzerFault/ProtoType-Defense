#pragma once
#include "pch.h"

#include "Test.h"
#include "GameController.h"

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

		GLfloat atkSpd = (GLfloat)Tower::baseAttackSpeed;
		int pierce = 3;

		GameController gameController;
	
	};

}

