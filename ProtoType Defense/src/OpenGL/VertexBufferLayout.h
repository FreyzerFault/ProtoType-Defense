#pragma once
#include "pch.h"

#include "GLDebugging.h"

struct VertexBufferElement
{
	GLuint type;
	GLuint count;		// coords
	GLuint normalized;
};

// Permite al VertexArray interpretar el Layout de sus Buffers
class VertexBufferLayout
{
public:
	VertexBufferLayout()
		: m_Stride(0)
	{
	}
	
	// Plantilla sin uso
	template<typename T>
	void Push(GLuint count)
	{
	}

	template<>
	void Push<GLfloat>(GLuint count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * sizeof(GLfloat);
	}

	template<>
	void Push<GLuint>(GLuint count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * sizeof(GLuint);
	}

	template<>
	void Push<GLubyte>(GLuint count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * sizeof(GLubyte);
	}

	template<>
	void Push<GLint>(GLuint count)
	{
		m_Elements.push_back({ GL_INT, count, GL_FALSE });
		m_Stride += count * sizeof(GLint);
	}

	inline std::vector<VertexBufferElement> getElements() const { return m_Elements; };
	inline GLuint getStride() const { return m_Stride; };


private:
	std::vector<VertexBufferElement> m_Elements;	// {positions + color + ...}
	GLuint m_Stride;							// Tamaño del array en bytes

};

