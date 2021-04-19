#include "ShaderManager.h"

ShaderManager::ShaderManager()
	: currentShader(nullptr)
{
}

void ShaderManager::add(const std::string& name)
{
	std::cout << "Adding shader " << name << std::endl;
	currentShader = &shaderList.emplace(name, getFolderPath() + name + ".shader").first->second;
	currentShaderName = name;
}

void ShaderManager::Bind(std::string name)
{
	currentShader = &shaderList.find(name)->second;
	currentShaderName = name;
	currentShader->Bind();
}

void ShaderManager::setTextureSlots(const uint32_t count) const
{
	std::vector<int> slots;
	slots.reserve(count);
	for (int i = 0; i < count; i++)
	{
		slots.push_back(i);
	}
	setUniform1iv("u_Texture", count, slots.at(0));
}
