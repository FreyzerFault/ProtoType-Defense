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

	GLuint offset = 0;

	const auto& elements = layout.getElements();
	for (GLuint i = 0; i < elements.size(); i++)
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
		offset += element.count * sizeof(element.type);
	}
}

void VertexArray::setDefaultBuffer(const VertexBuffer& vb) const
{
	Bind();
	vb.Bind();

	VertexBufferLayout layout;
	layout.Push<GLfloat>(3);	// POSITION
	layout.Push<GLfloat>(4);	// COLOR
	layout.Push<GLfloat>(2);	// TEXCOORDS
	layout.Push<GLfloat>(1);	// TEXID

	GLuint offset = 0;

	const auto& elements = layout.getElements();
	for (GLuint i = 0; i < elements.size(); i++)
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
		offset += element.count * sizeof(element.type);
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
