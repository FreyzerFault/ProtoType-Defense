#include "pch.h"
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

	setLayout();
}

void ShaderManager::Bind(const std::string& name)
{
	// Skip Binding if it's already binded
	if (currentShaderName != name)
	{
		currentShader = &shaderList.find(name)->second;
		currentShaderName = name;
		currentShader->Bind();
	}
}

void ShaderManager::setTextureSlots(const GLuint count) const
{
	std::vector<int> slots;
	slots.reserve(count);
	for (int i = 0; i < count; i++)
	{
		slots.push_back(i);
	}
	setUniform1iv("u_Texture", count, slots.at(0));
}

void ShaderManager::setLayout() const
{
	VertexBufferLayout& layout = currentShader->getLayout();
	if (currentShaderName == "NoTexture")
	{
		layout.Push<GLfloat>(3);
		layout.Push<GLfloat>(4);
	}
	else if (currentShaderName == "Basic")
	{
		layout.Push<GLfloat>(3);	// POSITION
		layout.Push<GLfloat>(4);	// COLOR
		layout.Push<GLfloat>(2);	// TEXCOORDS
		layout.Push<GLfloat>(1);	// TEXID
	}
}
