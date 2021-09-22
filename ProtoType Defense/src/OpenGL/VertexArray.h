#pragma once
#include "pch.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
	VertexArray();
	// No se permiten copias porque cada VAO tiene un ID unico
	VertexArray(const VertexArray& orig) = delete;
	VertexArray& operator=(const VertexArray& orig) = delete;
	~VertexArray();

	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void setDefaultBuffer(const VertexBuffer& vb) const; // Position 2D + Color RGB + TexCoords 2D + TexID

	void Bind() const;
	void Unbind() const;

private:
	GLuint m_RendererID;

};

