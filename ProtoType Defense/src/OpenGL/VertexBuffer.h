#pragma once
#include "pch.h"

#include "GLDebugging.h"

class VertexBuffer
{
public:
	VertexBuffer();
	VertexBuffer(const void* data, uint32_t size, uint32_t drawType = GL_STATIC_DRAW);
	VertexBuffer(uint32_t size); // Empty Buffer

	// No se permiten copias porque cada VAO tiene un ID unico
	VertexBuffer(const VertexBuffer& orig) = delete;
	VertexBuffer& operator=(const VertexBuffer& orig) = delete;
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	void setData(const void* data, uint32_t size, uint32_t drawType = GL_DYNAMIC_DRAW);
	void updateData(const void* data, uint32_t size);

private:
	uint32_t m_RendererID;

};

