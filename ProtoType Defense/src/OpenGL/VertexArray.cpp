#include "pch.h"
#include "VertexArray.h"

#include "GLDebugging.h"

VertexArray::VertexArray()
	: m_RendererID()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();

	uint32_t offset = 0;

	const auto& elements = layout.getElements();
	for (uint32_t i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];

		GLCall(glEnableVertexAttribArray(i)); // Indice del atributo a modificar

		GLCall(glVertexAttribPointer(i,	// Indice del Atributo a modificar (0 = position, 1 = color, 2 = texcoords, 3 = texID, 4 = normal)
			element.count,				// Tamaño (Coordenadas del atributo)
			element.type,
			element.normalized,			// Normalize? de gratis xd
			layout.getStride(),			// STRIDE = Vertex Size
			(const void*)offset));		// POINTER (offset) = Bytes entre el inicio del Vertice hasta el atributo (si falla castear a (const void*))

		// Aumentamos el offset en bytes
		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
	}
}

void VertexArray::setDefaultBuffer(const VertexBuffer& vb) const
{
	Bind();
	vb.Bind();

	VertexBufferLayout layout;
	layout.Push<float>(3);	// POSITION
	layout.Push<float>(4);	// COLOR
	layout.Push<float>(2);	// TEXCOORDS
	layout.Push<float>(1);	// TEXID

	uint32_t offset = 0;

	const auto& elements = layout.getElements();
	for (uint32_t i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];

		GLCall(glEnableVertexAttribArray(i)); // Indice del atributo a modificar

		GLCall(glVertexAttribPointer(i,	// Indice del Atributo a modificar (0 = position, 1 = color, 2 = texcoords, 3 = texID, 4 = normal)
			element.count,				// Tamaño (Coordenadas del atributo)
			element.type,
			element.normalized,			// Normalize? de gratis xd
			layout.getStride(),			// STRIDE = Vertex Size
			(const void*)offset));		// POINTER (offset) = Bytes entre el inicio del Vertice hasta el atributo (si falla castear a (const void*))

		// Aumentamos el offset en bytes
		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
