#pragma once
#include "GLDebugging.h"

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;

public:
	IndexBuffer(const unsigned int* data, unsigned int count, unsigned int type = GL_STATIC_DRAW);
	IndexBuffer(unsigned int count); // Buffer de indices vacio con espacio reservado count * sizeof(unsigned int)
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int getCount() const { return m_Count; };

	void setIndices(const void* data, unsigned int count);
	void updateIndices(const void* data, unsigned int count);
};

