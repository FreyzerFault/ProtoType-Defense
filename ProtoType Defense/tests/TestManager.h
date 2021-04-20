#pragma once
#include "Test.h"

#include "TestClearColor.h"
#include "TestBatchRendering.h"
#include "TestDynamicBuffer.h"
#include "TestShootDeltaTime.h"
#include "TestSendingWaves.h"

using namespace test;

class TestManager
{
public:
	TestManager();
	~TestManager();

	void addTests();

	void onUpdate(DeltaTime deltaTime) { currentTest->onUpdate(deltaTime); }
	void onRender() { currentTest->onRender(); }
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


