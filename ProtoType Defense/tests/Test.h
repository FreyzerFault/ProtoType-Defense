#pragma once
#include "pch.h"

#include "DeltaTime.h"

namespace test {
	class Test
	{
	public:
		Test();
		Test(glm::mat4 proj, glm::mat4 view, glm::mat4 model);
		virtual ~Test() = default;

		void setWindow(GLFWwindow* window) { this->window = window; };
		
		virtual void reset() {}
		
		virtual void onUpdate(DeltaTime deltaTime) {}
		virtual void onRender() {}
		virtual void onImGuiRender() {}

	protected:
		glm::mat4 proj;
		glm::mat4 view;
		glm::mat4 model;
		

		// TIMERS
		GLfloat shootTimer = 0;
		GLfloat enemyTimer = 0;

		GLFWwindow* window;
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
		Test*& m_CurrentTest; // Referencia al currentTest del TestManager (permite modificarlo)
		std::string m_CurrentTestName;
		std::vector< std::pair<std::string, std::function<Test*()>> > m_Tests; // Lista de Tests disponibles
	};

	template <typename T>
	void TestMenu::addTest(const std::string& name)
	{
		std::cout << "Adding test " << name << std::endl;
		// Stores the function that initialize the Test of type T
		// Therefor the test only initialize when we call for it
		auto newTest = []() { return new T(); };
		m_Tests.push_back(
			std::make_pair(name, newTest /*Test sin crear*/)
		);
	}
}
