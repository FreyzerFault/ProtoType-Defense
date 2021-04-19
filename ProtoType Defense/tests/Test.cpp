#include "Test.h"

#include "GlobalParameters.h"
#include "imgui.h"

namespace test {
	glm::mat4 Test::m_Proj(glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, -200.0f, 2000.0f));

	TestMenu::TestMenu(Test*& currentTestPointer)
		: m_CurrentTest(currentTestPointer)
	{
	}

	TestMenu::~TestMenu() = default;

	void TestMenu::onImGuiRender()
	{
		for (auto& test : m_Tests)
		{
			if (ImGui::Button(test.first.c_str()))
			{
				m_CurrentTest = test.second;
				m_CurrentTestName = test.first;
			}
		}
	}
}


