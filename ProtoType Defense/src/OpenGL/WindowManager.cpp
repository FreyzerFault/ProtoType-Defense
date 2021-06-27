#include "pch.h"
#include "WindowManager.h"

#include "GlobalParameters.h"
#include "Renderer.h"

WindowManager::WindowManager()
	: WindowManager(windowWidth, windowHeight,
		"Prototype Defence DEMO", 1)
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
		fpsTimer -= 1;
		fpsCounter = 0;
	}
}


void WindowManager::renderingLoop()
{
	time = (float)glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
		Renderer::clear();
		Renderer::setClearColor();

		ImGuiManager::startFrame();

		const DeltaTime deltaTime = getDeltaTime();
		
		// FPS
		updateFPS(deltaTime);
		
		if (testManager.isActive())
		{
			testManager.getTest()->setWindow(window);
			
			testManager.onUpdate(deltaTime);
			testManager.onRender();
			testManager.onImGuiRender();

			ImGui::Begin("FPS");
			ImGui::LabelText("FPS", std::to_string(fps).c_str());
			ImGui::End();
		}

		ImGuiManager::endFrame();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
