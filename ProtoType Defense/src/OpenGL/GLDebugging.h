#pragma once

#include <GL/glew.h>

#include <iostream>

// MACROS
#define ASSERT(x) if (!(x)) __debugbreak() // Para el programa si coge false

// Con GLCall() se puede rodear cada funcion de OpenGL
//  lo cual para el programa y muestra el codigo de ERROR por consola
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))
// He usado \enter para no tener que escribir la macro en una sola linea
// #x convierte a x en String (nombre de la funcion a la que se aplica)

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR); // or (!glGetError)
}

static bool GLLogCall(const char* function, const char* file, int line)
{
	if (const GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ")" << function <<
			" in " << file << " [" << line << "]" << std::endl;
		return false;
	}
	return true;
}

static void GLgetVersion()
{
	int MVersion, mVersion;
	glGetIntegerv(GL_MAJOR_VERSION, &MVersion);
	glGetIntegerv(GL_MINOR_VERSION, &mVersion);
	std::cout << "Using OpenGL " << MVersion << "." << mVersion << std::endl;
}
