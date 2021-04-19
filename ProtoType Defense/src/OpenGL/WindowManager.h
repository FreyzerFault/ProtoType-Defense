#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "TestManager.h"
#include "ImGuiManager.h"

class WindowManager
{
public:
	WindowManager();
	WindowManager(const uint32_t width, const uint32_t height, const std::string& title, const uint32_t monitor = 1);
	~WindowManager();

	void renderingLoop();

	void setup();
	void shutdown() const;
	
	GLFWwindow* getWindow() const { return window; }

private:
	GLFWwindow* window;

	ImGuiManager GUI;

	TestManager testManager;
};

