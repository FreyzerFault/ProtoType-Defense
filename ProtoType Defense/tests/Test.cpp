#include "pch.h"
#include "Test.h"

#include "GlobalParameters.h"

using namespace glm;

namespace test {

	Test::Test()
		: proj(ortho(0.f, (float)windowWidth, 0.f, (float)windowHeight, 1.f, 2000.f)), // Frustrum ORTONORMAL (0,windowXY), Near 1, Far 2K
		view(lookAt(vec3(0.f, 0.f, 250.f), vec3(0.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f))), // EYE (0,0,250) --> REFERENCE (0,0,0), ^ UP (0,1,0)
		model(1.f) // Model IDENTITY MATRIX
	{
	}

	Test::Test(glm::mat4 proj, glm::mat4 view, glm::mat4 model)
		: proj(proj), view(view), model(model)
	{
	}


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
				m_CurrentTest = test.second(); // Execute the initializing FUNCTION new T()
				m_CurrentTestName = test.first;
			}
		}
	}
}


