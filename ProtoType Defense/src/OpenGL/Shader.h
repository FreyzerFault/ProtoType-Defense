#pragma once

#include <string>
#include <unordered_map>
#include "glm.hpp"
#include "GLDebugging.h"

#define shaderFolderPath Shader::getFolderPath()

// Archivo .shader con codigo del vertex shader y el fragment shader 
struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};


class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	// UNIFORMS cache = +Efficiency
	mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;
public:
	Shader();
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// UNIFORMS
	void setUniform1i(const std::string& name, int value);
	void setUniform1iv(const std::string& name, unsigned int count, const int &value);
	void setUniform1f(const std::string& name, float value);
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniformMat4f(const std::string& name, const glm::mat4& matrix);

	void setTextureSlots(const unsigned int count); // Asigna al Uniforme u_Texture el vector de slots usados
	
	static std::string getFolderPath() { return "res/shaders/"; }

private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);

	GLint getUniformLocation(const std::string& name) const;
};
