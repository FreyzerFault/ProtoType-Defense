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
	currentTexture = &textureList.emplace(name, getFolderPath() + name + ".png").first->second;
	currentTextureName = name;

	Bind(slot);
}

void TextureManager::Bind(const std::string& name, int slot)
{
	currentTexture = &textureList.find(name)->second;
	currentTextureName = name;
	
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

glm::vec2 TextureManager::getSize(std::string& texName)
{
	Texture& texture = getTexture(texName);
	return glm::vec2(texture.getWidth(), texture.getHeight());
}
