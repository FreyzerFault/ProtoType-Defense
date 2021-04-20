#pragma once

#include <vector>
#include <string>
#include <functional>
#include <iostream>

#include "DeltaTime.h"
#include "Renderer.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "GameController.h"

namespace test {
	class Test
	{
	public:
		Test() = default;
		virtual ~Test() = default;

		virtual void reset() {}

		virtual void onUpdate(DeltaTime deltaTime) {}
		virtual void onRender() {}
		virtual void onImGuiRender() {}

	protected:
		static glm::mat4 m_Proj;

		// TIMERS
		float shootTimer = 0;
		float enemyTimer = 0;
		
		int fps = 60;
		float fpsTimer = 0;
		int fpsCounter = 0;
	};

	// Menu para elegir Tests
	class TestMenu final : public Test
	{
	public:

		explicit TestMenu(Test*& currentTestPointer);
		~TestMenu() override;
		
		void onImGuiRender() override;


		template <typename T>
		void addTest(const std::string& name);

		const std::string& getCurrentTestName() const { return m_CurrentTestName; }
		Test* getTest() const { return m_CurrentTest; }
		
	private:
		Test*& m_CurrentTest; // Referencia al puntero en main (permite modificarlo)
		std::string m_CurrentTestName;
		std::vector< std::pair<std::string, Test*> > m_Tests; // Lista de Tests disponibles
	};

	template <typename T>
	void TestMenu::addTest(const std::string& name)
	{
		std::cout << "Adding test " << name << std::endl;
		T* newTest = new T();
		m_Tests.push_back(
			std::make_pair(name, newTest /*Test sin crear*/)
		);
	}
}
