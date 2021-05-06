#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	GLCall(glGenBuffers(1, &m_RendererID));
}

VertexBuffer::VertexBuffer(const void* data, uint32_t size, uint32_t drawType)
{
	GLCall(glGenBuffers(1, &m_RendererID)); // (Nº buffers, direccion donde queremos escribir el buffer)
	// Se pueden generar varios buffers y bindear el que prefieras antes de dibujar
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // (tipo de buffer, buffer para obtener id (no es necesario modificarlo, asi que nada de &))

	// Para insertar datos al buffer o sustituirlos:
	GLCall(glBufferData(GL_ARRAY_BUFFER, // target = target de glBindBuffer
		size, // tamaño del buffer = 6 * sizeof(float) = sizeof(positions) (puede no ser preciso el ultimo)
		data,  // Direccion o puntero a los datos
		drawType));	// STATIC = una/pocas modificaciones / DYNAMIC = muchas ___ DRAWN para dibujar xd
}

VertexBuffer::VertexBuffer(uint32_t size)
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

void VertexBuffer::setData(const void* data, uint32_t size, uint32_t drawType)
{
	Bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, drawType)); // Offset de 0
}

void VertexBuffer::updateData(const void* data, uint32_t size)
{
	Bind();
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data)); // Offset de 0
}
