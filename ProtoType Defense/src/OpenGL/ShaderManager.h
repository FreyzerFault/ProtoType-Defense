#pragma once
#include "pch.h"

#include "Shader.h"

#define shaderFolderPath ShaderManager::getFolderPath()

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager() = default;
	
	void add(const std::string& name);

	void Bind(const std::string& name);
	void Bind() const { currentShader->Bind(); }
	static void unBind() { GLCall(glUseProgram(0)); }

	// UNIFORMS
	void setUniform1i(const std::string& name, int value) const { currentShader->setUniform1i(name, value); }
	void setUniform1iv(const std::string& name, uint32_t count, const int& value) const { currentShader->setUniform1iv(name, count, value); }
	void setUniform1f(const std::string& name, float value) const { currentShader->setUniform1f(name, value); }
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const { currentShader->setUniform4f(name, v0, v1, v2, v3); }
	void setUniformMat4f(const std::string& name, const glm::mat4& matrix) const { currentShader->setUniformMat4f(name, matrix); }

	void setTextureSlots(const uint32_t count) const; // Asigna al Uniforme u_Texture el vector de slots usados

	Shader& getShader() const { return *currentShader; }
	const std::string& getShaderName() const { return currentShaderName; }
	
	static std::string getFolderPath() { return "res/shaders/"; }

	// Create the vertex layout for the shader
	void setLayout() const;

private:
	std::unordered_map<std::string, Shader> shaderList;
	Shader* currentShader;
	std::string currentShaderName;
	
};

