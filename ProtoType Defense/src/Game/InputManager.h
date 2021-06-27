#pragma once
#include "GameController.h"

// Stores Callback Functions to controll inputs
class InputManager
{
public:
	InputManager(GameController* gc);
	~InputManager() = default;

	static void setCallbacks(GLFWwindow* window);

	// Clicks on a Tile -> Place a Tower
	static void placeTowerInTileCallback(GLFWwindow* window, int button, int action, int mods);

	GameController* getGameController() const { return gameController; }
	
private:
	GameController* gameController;
	
};

