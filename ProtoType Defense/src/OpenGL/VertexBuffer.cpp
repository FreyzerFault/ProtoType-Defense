#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size, unsigned int type)
{
	GLCall(glGenBuffers(1, &m_RendererID)); // (N� buffers, direccion donde queremos escribir el buffer)
	// Se pueden generar varios buffers y bindear el que prefieras antes de dibujar
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // (tipo de buffer, buffer para obtener id (no es necesario modificarlo, asi que nada de &))

	// Para insertar datos al buffer o sustituirlos:
	GLCall(glBufferData(GL_ARRAY_BUFFER, // target = target de glBindBuffer
		size, // tama�o del buffer = 6 * sizeof(float) = sizeof(positions) (puede no ser preciso el ultimo)
		data,  // Direccion o puntero a los datos
		type));	// STATIC = una/pocas modificaciones / DYNAMIC = muchas ___ DRAWN para dibujar xd
}

VertexBuffer::VertexBuffer(unsigned int size)
{
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	// NULLPTR = Reserva espacio de size para datos
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::setData(const void* data, unsigned int size)
{
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW)); // Offset de 0
}

void VertexBuffer::updateData(const void* data, unsigned int size)
{
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data)); // Offset de 0
}