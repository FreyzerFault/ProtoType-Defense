#pragma once
#include "pch.h"

#include "Test.h"

using namespace test;

class TestManager
{
public:
	TestManager();
	~TestManager();

	void addTests();

	void onUpdate(DeltaTime deltaTime) const { currentTest->onUpdate(deltaTime); }
	void onRender() const { currentTest->onRender(); }
	void onImGuiRender();

	template <typename T>
	void add(const std::string& title);

	Test* getTest() const { return currentTest; }

	bool isActive() const { return currentTest != nullptr; }

private:
	Test* currentTest;
	TestMenu testMenu;
};

template <typename T>
void TestManager::add(const std::string& title)
{
	testMenu->addTest<T>(title);
}


