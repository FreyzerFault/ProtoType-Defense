#pragma once

#include <string>
#include <unordered_map>
#include "glm.hpp"
#include "GLDebugging.h"


// Archivo .shader con codigo del vertex shader y el fragment shader 
struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};


class Shader
{
public:
	Shader();
	explicit Shader(const std::string& filepath);
	~Shader();

	void Bind() const;

	// UNIFORMS
	void setUniform1i(const std::string& name, int value) const;
	void setUniform1iv(const std::string& name, uint32_t count, const int& value) const;
	void setUniform1f(const std::string& name, float value) const;
	void setUniform4f(const std::string& name, float f0, float f1, float f2, float f3) const;
	void setUniformMat4f(const std::string& name, const glm::mat4& matrix) const;

private:
	std::string m_FilePath;
	uint32_t m_RendererID;
	
	// UNIFORMS cache = +Efficiency
	mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;

	
	ShaderProgramSource ParseShader(const std::string& filepath) const;
	uint32_t CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	uint32_t CompileShader(uint32_t type, const std::string& source);

	GLint getUniformLocation(const std::string& name) const;
};
