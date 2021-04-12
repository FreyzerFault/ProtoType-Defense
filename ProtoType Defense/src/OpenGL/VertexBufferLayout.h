#pragma once

#include <vector>

#include "GLDebugging.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;		// coords
	unsigned int normalized;

	static unsigned int getSizeOfType(unsigned int type) // en bytes
	{
		switch (type)
		{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}
};

// Permite al VertexArray interpretar el Layout de sus Buffers
class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;	// {positions + color + ...}
	unsigned int m_Stride;							// Tamaño del array en bytes
public:
	VertexBufferLayout()
		: m_Stride(0)
	{
	}

	// Plantilla sin uso
	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement> getElements() const { return m_Elements; };
	inline unsigned int getStride() const { return m_Stride; };
};

