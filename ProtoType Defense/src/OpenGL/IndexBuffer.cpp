#include "pch.h"
#include "IndexBuffer.h"
#include "GLDebugging.h"

IndexBuffer::IndexBuffer(): m_Count(0)
{
	glGenBuffers(1, &m_RendererID);
}

IndexBuffer::IndexBuffer(const GLuint* data, GLuint count, GLuint type)
	: m_Count(count)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); // ELEMENT ARRAY BUFFER

	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		count * sizeof(GLuint), // tamaño del buffer = 6 * sizeof(GLfloat) = sizeof(positions) (puede no ser preciso el ultimo)
		data,  // Direccion o puntero a los datos
		type);	// STATIC = una/pocas modificaciones / DYNAMIC = muchas ___ DRAW para dibujar xd
}

IndexBuffer::IndexBuffer(GLuint count)
	: m_Count(count)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); // ELEMENT ARRAY BUFFER

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
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

void IndexBuffer::setIndices(const void* data, GLuint count)
{
	m_Count = count;
	Bind();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_DYNAMIC_DRAW));
}

void IndexBuffer::updateIndices(const void* data, GLuint count)
{
	m_Count = count;
	Bind();
	GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, count * sizeof(GLuint), data));
}
