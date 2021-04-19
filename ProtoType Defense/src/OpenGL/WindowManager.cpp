#include "WindowManager.h"

#include "GlobalParameters.h"


WindowManager::WindowManager()
	: WindowManager(windowWidth, windowHeight,
		"Guapo el que lo lea", 1)
{
}

WindowManager::WindowManager(const uint32_t width, const uint32_t height, const std::string& title, const uint32_t monitor)
	: window(glfwCreateWindow(
		width, height,
		title.c_str(),nullptr, nullptr)), GUI(window)
{
	glfwMakeContextCurrent(window);
}

WindowManager::~WindowManager() = default;

void WindowManager::setup()
{
	// OpenGL Flags
	Renderer::glEnableFlags();
	
	GUI.setup(window);

	testManager.addTests();
}

void WindowManager::shutdown() const
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}


void WindowManager::renderingLoop()
{
	float lastFrameTime = (float)glfwGetTime();
	
	while (!glfwWindowShouldClose(window))
	{
		Renderer::clear();
		Renderer::setClearColor();

		GUI.startFrame();

		// DELTA TIME
		const float time = (float)glfwGetTime(); // Secs
		const DeltaTime deltaTime = time - lastFrameTime;
		lastFrameTime = time;
		
		if (testManager.isActive())
		{
			testManager.onUpdate(deltaTime);
			testManager.onRender();
			testManager.onImGuiRender();
		}


		GUI.endFrame();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
