#pragma once
#include <unordered_map>

#include "Texture.h"

#define textureFolderPath TextureManager::getFolderPath()

static int MAX_TEXTURE_SLOTS = 32;

class TextureManager
{

public:
	TextureManager();
	~TextureManager() = default;

	void add(const std::string& name, int slot = 0);

	void Bind(const std::string& name, int slot = 0);
	void Bind(int slot = 0);
	static void unBind();


	static std::string getFolderPath() { return "res/textures/"; }

	int* getTexIndeces() const { return texIndices; }

	// Current
	Texture& getTexture() const { return *currentTexture; }
	const std::string& getTextureName() const { return currentTextureName; }
	
	// by Slot
	Texture& getTexture(int slot) const { return *textureSlots.find(slot)->second; }
	const std::string& getTextureName(int slot) const { return textureSlots.find(slot)->second->getName(); }

private:
	std::unordered_map<std::string, Texture> textureList;
	Texture* currentTexture;
	std::string currentTextureName;

	std::unordered_map<int, Texture*> textureSlots;

	int* texIndices;
	

};

