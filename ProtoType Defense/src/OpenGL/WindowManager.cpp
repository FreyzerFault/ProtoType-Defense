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
		title.c_str(),nullptr, nullptr)), GUI(window),
	time((float)glfwGetTime())
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

DeltaTime WindowManager::getDeltaTime()
{
	const float lastFrameTime = time;
	const float frameTime = (float)glfwGetTime(); // Secs
	const DeltaTime deltaTime = frameTime - lastFrameTime;
	time = frameTime;
	return deltaTime;
}

void WindowManager::updateFPS(DeltaTime deltaTime)
{
	fpsCounter++;
	fpsTimer += deltaTime;

	if (fpsTimer >= 1) // Every Sec
	{
		fps = fpsCounter;
		//std::cout << "FPS: " << getFPS() << std::endl;
		fpsTimer -= 1;
		fpsCounter = 0;
	}
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
		DeltaTime deltaTime = getDeltaTime();

		// FPS
		updateFPS(deltaTime);

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
