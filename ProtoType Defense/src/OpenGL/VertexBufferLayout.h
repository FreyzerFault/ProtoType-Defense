#pragma once

#include <vector>

#include "GLDebugging.h"

struct VertexBufferElement
{
	uint32_t type;
	uint32_t count;		// coords
	uint32_t normalized;

	static uint32_t getSizeOfType(uint32_t type) // en bytes
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
public:
	VertexBufferLayout()
		: m_Stride(0)
	{
	}

	// Plantilla sin uso
	template<typename T>
	void Push(uint32_t count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(uint32_t count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<uint32_t>(uint32_t count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(uint32_t count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement> getElements() const { return m_Elements; };
	inline uint32_t getStride() const { return m_Stride; };


private:
	std::vector<VertexBufferElement> m_Elements;	// {positions + color + ...}
	uint32_t m_Stride;							// Tamaño del array en bytes

};

