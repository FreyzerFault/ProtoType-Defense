#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count, unsigned int type)
	: m_Count(count)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); // ELEMENT ARRAY BUFFER

	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		count * sizeof(unsigned int), // tamaño del buffer = 6 * sizeof(float) = sizeof(positions) (puede no ser preciso el ultimo)
		data,  // Direccion o puntero a los datos
		type);	// STATIC = una/pocas modificaciones / DYNAMIC = muchas ___ DRAW para dibujar xd
}

IndexBuffer::IndexBuffer(unsigned int count)
	: m_Count(count)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); // ELEMENT ARRAY BUFFER

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), nullptr, GL_DYNAMIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind()const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void IndexBuffer::setIndices(const void* data, unsigned int count)
{
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_DYNAMIC_DRAW));
}

void IndexBuffer::updateIndices(const void* data, unsigned int count)
{
	GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, count * sizeof(unsigned int), data));
}
