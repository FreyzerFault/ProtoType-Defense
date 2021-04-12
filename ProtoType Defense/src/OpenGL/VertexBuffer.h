#pragma once
#include "GLDebugging.h"

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size, unsigned int type = GL_STATIC_DRAW);
	VertexBuffer(unsigned int size); // Empty Buffer

	// No se permiten copias porque cada VAO tiene un ID unico
	VertexBuffer(const VertexBuffer& orig) = delete;
	VertexBuffer& operator=(const VertexBuffer& orig) = delete;
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	void setData(const void* data, unsigned int size);
	void updateData(const void* data, unsigned int size);
};

