#pragma once
#include "pch.h"

#include "TestManager.h"
#include "ImGuiManager.h"
#include "InputManager.h"

class WindowManager
{
public:
	WindowManager();
	WindowManager(const uint32_t width, const uint32_t height, const std::string& title, const uint32_t monitor = 1);
	~WindowManager();

	void renderingLoop();

	void setup();
	void shutdown() const;

	// FPS
	DeltaTime getDeltaTime();
	void updateFPS(DeltaTime deltaTime);
	int getFPS() const { return fps; }
	
	GLFWwindow* getWindow() const { return window; }

private:
	GLFWwindow* window;

	ImGuiManager GUI;

	TestManager testManager;

	// Program Time
	float time;
	// FPS
	float fpsTimer = 0;
	int fpsCounter = 0;
	int fps;
};

