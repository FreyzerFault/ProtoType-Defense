#include "pch.h"
#include "InputManager.h"

using namespace glm;

// Need a static instance of the InputManager to work in the static callbacks with the GameController
static InputManager* interface;


InputManager::InputManager(GameController* gc)
	: gameController(gc)
{
	interface = this;
}

void InputManager::setCallbacks(GLFWwindow* window)
{
	glfwPollEvents();
	glfwSetMouseButtonCallback(window, placeTowerInTileCallback);
}

void InputManager::placeTowerInTileCallback(GLFWwindow* window, int button, int action, int mods)
{
	// Ignore the Game when using the ImGui Windows
	if (ImGui::GetIO().WantCaptureMouse) return;
	
	// Don't Trigger PRESS inputs, only RELEASES
	if (action != GLFW_RELEASE) return;

	GameController& gc = *interface->getGameController();
	
	// Deselect if any tower selected
	gc.deselectTower();

	// Mouse Position
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	y = windowHeight - y;
	const vec2 mousePos = vec2(x, y);

	
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		// If selected an empty platform
		if (gc.getMap().getPlatform(mousePos) != nullptr &&
			gc.getMap().getPlatform(mousePos)->isEmpty())
		{
			gc.placeTower(mousePos, TypeTower::piercer);
			std::cout << "Placed Tower in (" << x << "," << y << ")" << std::endl;
		}
		else
			// Select the Tower
			gc.selectTower(mousePos);
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		// Right Click -> Sell Tower
		if (gc.sellTower(mousePos))
			std::cout << "Sold Tower in (" << x << "," << y << ")" << std::endl;
		break;
	}
}

