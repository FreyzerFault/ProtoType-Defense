#include "pch.h"
#include "TestSendingWaves.h"

#include "GlobalParameters.h"

using namespace test;
using namespace glm;

TestSendingWaves::TestSendingWaves()
	: Test(), inputManager(&gameController)
		
{
	gameController.startGame();
}

TestSendingWaves::~TestSendingWaves() = default;


void TestSendingWaves::reset()
{
	gameController.reset();
}

void TestSendingWaves::onUpdate(DeltaTime deltaTime)
{
	// EACH FRAME CALCULATIONS

	InputManager::setCallbacks(window);

	if (gameController.isActive())
		gameController.update(deltaTime);
	
}

void TestSendingWaves::onRender()
{
	Renderer::clear();
	Renderer::setClearColor();

	// ORTONORMAL
	proj = ortho(0.f, (float)windowWidth, 0.f, (float)windowHeight, 1.f, 2000.f);
	view = lookAt(glm::vec3(0.0f, 0.0f, 250.f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	// PERSPECTIVE
	if (viewPerspective)
	{
		proj = perspective(90.f, (float)windowWidth / (float)windowHeight, 1.f, 2000.f);
		view = lookAt(glm::vec3(windowCenterX - 250.f, windowCenterY + 250.f, 250.f), glm::vec3(windowCenterX - 210.f, windowCenterY, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	// MODEL
	model = glm::mat4(1.0f);

	const mat4 mvp = proj * view * model;

	gameController.render(mvp);
}

void TestSendingWaves::onImGuiRender()
{
	// GUI Buttons

	if (ImGui::Button("Reset")) reset();


	ImGui::Separator();
	ImGui::Separator();

	ImGui::Text("CONTROLS:");

	ImGui::Separator();
	
	ImGui::Text("Left  Click on Tile  - Place a Tower on the Tile");
	ImGui::Text("Left  Click on Tower - Select the Tower");
	ImGui::Text("Right Click on Tower - Sell a Tower");

	ImGui::Separator();
	ImGui::Separator();
	

	// Sound Volume

	ImGui::SliderInt("Global Volume", &gameController.getAudioManager().getVolume(), 0, 100);
	ImGui::SliderInt("Music Volume", &gameController.getAudioManager().getMusicVolume(), 0, MIX_MAX_VOLUME);
	ImGui::SliderInt("SFX Volume", &gameController.getAudioManager().getSFXVolume(), 0, MIX_MAX_VOLUME);
	gameController.getAudioManager().updateVolume();

	if (ImGui::Button("Next Song")) gameController.getAudioManager().nextSong();

	ImGui::Separator();
	
	// GAME SPEED
	ImGui::LabelText("Game Speed", std::to_string(gameController.getSpeed()).c_str());
	
	if (ImGui::Button("<<")) gameController.fastForward(25);
	if (ImGui::Button("<")) gameController.fastForward(50);
	
	if (gameController.isActive())
		if (ImGui::Button("Pause")) gameController.pauseGame();
		else;
	else
		if (ImGui::Button("Play")) gameController.resumeGame();

	if (ImGui::Button(">")) gameController.fastForward(200);
	if (ImGui::Button(">>")) gameController.fastForward(400);

	ImGui::Separator();
	
	// HITBOX
	ImGui::Checkbox("Show Hitbox", &gameController.areHitboxActive());


	ImGui::Separator();

	// VIEW PERSPECTIVE / ORTOGRAPHIC
	ImGui::Text("View:");
	if (ImGui::Button("Perspective")) viewPerspective = true;
	if (ImGui::Button("Ortographic")) viewPerspective = false;


	ImGui::Separator();

	// TOWER OPTIONS

	// If a Tower is Select show Tower Options
	
	if (gameController.getSelectedTower() != nullptr)
	{
		// AIMING PRIORITY
		bool first = true, last = false, strong = false, weak = false;
	
		const char* priorities[]{ "First", "Last", "Strong", "Weak" };
		ImGui::Combo("Priority", &selectedPrior, priorities, IM_ARRAYSIZE(priorities));

		Priority prior = Priority::first;
		switch (selectedPrior)
		{
		case 0:
			prior = Priority::first;
			break;
		case 1:
			prior = Priority::last;
			break;
		case 2:
			prior = Priority::strong;
			break;
		case 3:
			prior = Priority::weak;
			break;
		default: ;
		}

		gameController.getSelectedTower()->setPriority(prior);
	}


	ImGui::Separator();

	ImGui::LabelText("Money", (std::to_string(gameController.getMoney())).c_str());
	ImGui::LabelText("Lives", (std::to_string(gameController.getLives())).c_str());
}
