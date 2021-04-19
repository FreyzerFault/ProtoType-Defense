#include "TestManager.h"

#include "imgui.h"

using namespace test;

TestManager::TestManager()
	: currentTest(nullptr), testMenu(currentTest)
{
	currentTest = &testMenu;
}

TestManager::~TestManager() = default;

void TestManager::addTests()
{
	testMenu.addTest<TestClearColor>("Clear Color");
	/*testMenu.addTest<TestSprite>("Sprite");
	testMenu.addTest<TestBatchRendering>("Batch Rendering");
	testMenu.addTest<TestDynamicSprites>("Dynamic Sprites");
	testMenu.addTest<TestDynamicBuffer>("Dynamic Buffer");
	testMenu.addTest<TestThreads>("Threads");*/
	testMenu.addTest<TestShootDeltaTime>("Delta Time Shooting");
}

void TestManager::onImGuiRender()
{
	ImGui::Begin("Test");

	// Return to Tests Menu
	if (currentTest != &testMenu && ImGui::Button("<-"))
	{
		currentTest = &testMenu;
	}

	currentTest->onImGuiRender();
	
	ImGui::End();
}

