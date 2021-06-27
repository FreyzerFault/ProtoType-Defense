#include "pch.h"
#include "TestAudio.h"
#include "imgui.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "GlobalParameters.h"
#include "Renderer.h"
#include "Objects/Projectile.h"

using namespace test;

TestAudio::TestAudio()
	: Test(), renderer(3)
{
	audioManager.addSong("Blue Sphere Stage (8-BIT) - Sonic Mania");
	audioManager.addSong("Donkey Kong Country Theme Restored to HD");
	audioManager.addSong("Hi-Spec Robo Go 8-bit - Sonic Mania [Hardboiled Heavies Theme] (0CC-Famitracker, 2A03)");
	audioManager.addSong("Nokia 3220 Ringtone - Espionage  (Audio Original)");
	audioManager.addSong("Sonic Mania - Stardust Speedway Act 1 8 Bit Remix");
	audioManager.addSong("Studiopolis Act 1 (8-BIT) - Sonic Mania");

	audioManager.addSound("coin");
	audioManager.addSound("laser");
	audioManager.addSound("pop");
}

TestAudio::~TestAudio() = default;

void TestAudio::reset()
{
	audioManager.playSong("Blue Sphere Stage (8-BIT) - Sonic Mania");
	AudioManager::pauseMusic();
}

void TestAudio::onUpdate(DeltaTime deltaTime)
{
	if (platform != nullptr)
	{
		Tower* tower = platform->getTower();
		tower->aimPredictive(*enemy);
		tower->shoot(deltaTime);
		tower->moveProjectiles(deltaTime);
		
		auto itP = tower->getProjectiles().begin();

		while (itP != tower->getProjectiles().end())
		{
			Projectile& projectile = *itP;

			if (projectile.impact(enemy->getHitbox()))
			{
				audioManager.playSound("pop");
				enemy->getHit(tower->getDmg());
			}

			// If projectile pierce is <= 0, it's removed
			if (projectile.getPierce() <= 0)
			{
				const auto itaux = itP;
				++itP;
				tower->getProjectiles().erase(itaux);
			}
			else
				++itP;
		}
	}
	if (enemy != nullptr)
	{
		enemy->move(enemy->getSpeed() * 4 * deltaTime);
		enemy->rotate(enemy->getSpeed() * PI / 100 * deltaTime);
	}
}

void TestAudio::onRender()
{
	Renderer::setClearColor();
	Renderer::clear();

	// Scene MVP
	glm::mat4 mvp(proj * view * model);
	renderer.setMVP(mvp);

	if (platform != nullptr)
	{
		renderer.draw(platform->getTower()->getSprite());
		for (Projectile& projectile : platform->getTower()->getProjectiles())
			renderer.draw(projectile.getSprite());
	}
	if (enemy != nullptr)
	{
		renderer.draw(enemy->getSprite());
	}

}

void TestAudio::onImGuiRender()
{
	// GUI Buttons

	if (ImGui::Button("Reset")) reset();


	ImGui::Separator();

	ImGui::SliderInt("Global Volume", &audioManager.getVolume(), 0, 100);
	ImGui::SliderInt("Music Volume", &audioManager.getMusicVolume(), 0, MIX_MAX_VOLUME);
	ImGui::SliderInt("SFX Volume", &audioManager.getSFXVolume(), 0, MIX_MAX_VOLUME);
	audioManager.updateVolume();



	ImGui::Separator();

	ImGui::Text("SFX:");
	
	if (ImGui::Button("Play Coin Sound"))
		audioManager.playSound("coin");

	if (ImGui::Button("Play Laser Sound"))
		audioManager.playSound("laser");

	if (ImGui::Button("Play Pop Sound"))
		audioManager.playSound("pop");
	

	ImGui::Separator();

	ImGui::Text("Music:");
	
	if (ImGui::Button("PAUSE Music"))
		AudioManager::pauseMusic();
	if (ImGui::Button("RESUME Music"))
		AudioManager::resumeMusic();

	ImGui::Separator();
	
	if (ImGui::Button("Play Blue Sphere Theme"))
		audioManager.playSong("Blue Sphere Stage (8-BIT) - Sonic Mania");
	
	if (ImGui::Button("Play Donkey Kong Theme"))
		audioManager.playSong("Donkey Kong Country Theme Restored to HD");
	
	if (ImGui::Button("Play Hardboiled Heavies"))
		audioManager.playSong("Hi-Spec Robo Go 8-bit - Sonic Mania [Hardboiled Heavies Theme] (0CC-Famitracker, 2A03)");
	
	if (ImGui::Button("Play Espionage"))
		audioManager.playSong("Nokia 3220 Ringtone - Espionage  (Audio Original)");
	
	if (ImGui::Button("Play Stardust Speedway"))
		audioManager.playSong("Sonic Mania - Stardust Speedway Act 1 8 Bit Remix");

	if (ImGui::Button("Play Studiopolis"))
		audioManager.playSong("Studiopolis Act 1 (8-BIT) - Sonic Mania");

	
	ImGui::Separator();

	if (ImGui::Button("Spawn Tower & Enemy"))
	{
		platform = new Platform(glm::vec3(200, 200, 0), 64);
		platform->placeTower(*new Tower(platform));
		enemy = new Enemy(glm::vec3(300.f, 300.f, 0.f));
	}
		
}
