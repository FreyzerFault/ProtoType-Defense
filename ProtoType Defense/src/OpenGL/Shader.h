#pragma once
#include "pch.h"

#include "VertexBufferLayout.h"


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
	void setUniform1iv(const std::string& name, GLuint count, const int& value) const;
	void setUniform1f(const std::string& name, GLfloat value) const;
	void setUniform4f(const std::string& name, GLfloat f0, GLfloat f1, GLfloat f2, GLfloat f3) const;
	void setUniformMat4f(const std::string& name, const glm::mat4& matrix) const;

	//LAYOUT
	VertexBufferLayout& getLayout() { return layout; }
	void setLayout(VertexBufferLayout& newlayout) { layout = newlayout; }

private:
	std::string m_FilePath;
	GLuint m_RendererID;

	VertexBufferLayout layout;
	
	// UNIFORMS cache = +Efficiency
	mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;

	
	ShaderProgramSource ParseShader(const std::string& filepath) const;
	GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	GLuint CompileShader(GLuint type, const std::string& source);

	GLint getUniformLocation(const std::string& name) const;
};
