#pragma once

#include <vector>
#include <string>
#include <functional>
#include <iostream>

#include "DeltaTime.h"

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
	};

	// Menu para elegir Tests
	class TestMenu final : public Test
	{
	private:
		Test*& m_CurrentTest; // Referencia al puntero en main (permite modificarlo)
		std::string m_CurrentTestName;
		std::vector< std::pair<std::string, Test*> > m_Tests; // Lista de Tests disponibles

	public:

		explicit TestMenu(Test*& currentTestPointer);
		void onImGuiRender() override;

		std::string getCurrentTestName() const { return m_CurrentTestName; }

		template <typename T>
		void addTest(const std::string& name)
		{
			std::cout << "Adding test " << name << std::endl;
			T* newTest = new T();
			m_Tests.push_back(
				std::make_pair(name, newTest /*Test sin crear*/)
			);
		}
	};
}
