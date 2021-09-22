#include "pch.h"
#include "TextureManager.h"

#include "GLDebugging.h"

TextureManager::TextureManager()
	: currentTexture(nullptr), texIndices(nullptr)
{
	// Get Max Texture Slot Capacity
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &MAX_TEXTURE_SLOTS);
	texIndices = new int[MAX_TEXTURE_SLOTS];
	for (int i = 0; i < MAX_TEXTURE_SLOTS; i++)
	{
		texIndices[i] = i;
	}
}

void TextureManager::add(const std::string& name, int slot)
{
	std::cout << "Adding Texture " << name << " into Slot " << slot << std::endl;
	Texture* texture = &textureList.emplace(name, getFolderPath() + name + ".png").first->second;
	currentTexture = texture;
	currentTextureName = name;

	// If first texture --> default texture
	if (defaultTexture == nullptr)
		defaultTexture = texture;

	Bind(slot);
}

void TextureManager::Bind(const std::string& name, int slot)
{
	Texture* texture = getTexture(name);
	
	currentTexture = texture;
	currentTextureName = texture->getName();

	// If no texture exists with that name, assign the default to the slot given
	// It's a copy from slot 0 to slot X, to fill empty slots with the default
	
	Bind(slot);
}

void TextureManager::Bind(int slot)
{
	ASSERT(slot <= MAX_TEXTURE_SLOTS);
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	
	currentTexture->Bind();
	textureSlots.insert_or_assign(slot, currentTexture);
}

void TextureManager::unBind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture* TextureManager::getTexture(const std::string& name)
{
	auto it = textureList.find(name);
	if (it == textureList.end())
		return defaultTexture;
	return &it->second;
}

glm::vec2 TextureManager::getSize(std::string& texName)
{
	Texture* texture = getTexture(texName);
	return glm::vec2(texture->getWidth(), texture->getHeight());
}
