#include "pch.h"
#include "Shader.h"

#include "ShaderManager.h"

Shader::Shader()
	: Shader(shaderFolderPath + "Basic.shader")
{

}

Shader::Shader(const std::string& filepath)
	:m_FilePath(filepath), m_RendererID(0)
{
	const ShaderProgramSource source = ParseShader(filepath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
	Bind();
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}






// UNIFORMS:

void Shader::setUniform1i(const std::string& name, int value) const
{
	GLCall(glUniform1i(getUniformLocation(name), value));
}

void Shader::setUniform1iv(const std::string& name, GLuint count, const int& value) const
{
	GLCall(glUniform1iv(getUniformLocation(name), count, &value));
}

void Shader::setUniform1f(const std::string& name, GLfloat value) const
{
	GLCall(glUniform1f(getUniformLocation(name), value));
}

void Shader::setUniform4f(const std::string& name, GLfloat f0, GLfloat f1, GLfloat f2, GLfloat f3) const
{
	GLCall(glUniform4f(getUniformLocation(name), f0, f1, f2, f3));
}

void Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix) const
{
	GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}



GLint Shader::getUniformLocation(const std::string& name) const
{
	// Si ya esta registrado el Uniform cogemos ese
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	// Si no creamos otro en una nueva direccion que guardamos en la cache
	GLCall(GLint location = glGetUniformLocation(m_RendererID, name.c_str()));

	if (location == -1)
		std::cout << "ERROR: Uniform '" << name << "' doesn't exist!!!" << std::endl;

	m_UniformLocationCache[name] = location;
	return location;
}


// Processing Shader

ShaderProgramSource Shader::ParseShader(const std::string& filepath) const
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2]; // 1 stream para vertex y otro para fragment
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos) // npos = invalid string position
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			if (type != ShaderType::NONE)
				ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

GLuint Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLuint program = glCreateProgram();
	GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));
	// Attach hace copia de los Shaders asi que puedo eliminarlos
	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}

GLuint Shader::CompileShader(GLuint type, const std::string& source)
{
	GLCall(GLuint id = glCreateShader(type));

	const char* src = source.c_str(); // c_str() = puntero a principio del string (Tener cuidao de que el string no se elimine)

	// Mete un source code al shader (sustituyendo si habia alguno)
	GLCall(glShaderSource(
		id,	// Handle del Shader
		1,				// Nº strings
		&src,			// Puntero a un array de punteros a strings (como es 1 string => direccion del string)
		nullptr));		// Puntero a array de tamaños de cada array (si es solo uno dejar nullptr)

	GLCall(glCompileShader(id));

	// ERROR HANDLING:
	int result;
	// iv = int vector (puntero a int)
	GLCall(glGetShaderiv(
		id,		// id del Shader
		GL_COMPILE_STATUS,	// Parametro
		&result));			// Direccion donde se almacenara el resultado

	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

		char* message = (char*)_malloca(length * sizeof(char));

		GLCall(glGetShaderInfoLog(id, length, &length, message));

		std::cout << "Failed to compile "
			<< (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< " shader!!!" << std::endl;
		std::cout << message << std::endl;

		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;
}

