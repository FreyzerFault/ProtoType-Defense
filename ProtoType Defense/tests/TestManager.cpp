#include "pch.h"
#include "TestManager.h"


#include "TestAudio.h"
#include "TestClearColor.h"
#include "TestSendingWaves.h"
#include "TestShootDeltaTime.h"

using namespace test;

TestManager::TestManager()
	: currentTest(nullptr), testMenu(currentTest)
{
	currentTest = &testMenu;
}

TestManager::~TestManager()
{
	if (currentTest != &testMenu) delete currentTest;
}

void TestManager::addTests()
{
	testMenu.addTest<TestClearColor>("Clear Color");
	/*testMenu.addTest<TestSprite>("Sprite");
	testMenu.addTest<TestBatchRendering>("Batch Rendering");
	testMenu.addTest<TestDynamicSprites>("Dynamic Sprites");
	testMenu.addTest<TestDynamicBuffer>("Dynamic Buffer");*/
	testMenu.addTest<TestShootDeltaTime>("Shooting Test");
	testMenu.addTest<TestAudio>("Audio Test");
	testMenu.addTest<TestSendingWaves>("Game Demo");
}

void TestManager::onImGuiRender()
{
	ImGui::Begin("Test");
	
	// Return to Tests Menu
	if (currentTest != &testMenu && ImGui::Button("<-"))
	{
		delete currentTest;
		currentTest = &testMenu;
	}

	currentTest->onImGuiRender();
	
	ImGui::End();
}

