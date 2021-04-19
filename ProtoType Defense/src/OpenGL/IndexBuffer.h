#pragma once
#include "GLDebugging.h"

class IndexBuffer
{
public:
	IndexBuffer(const uint32_t* data, uint32_t count, uint32_t type = GL_STATIC_DRAW);
	IndexBuffer(uint32_t count); // Buffer de indices vacio con espacio reservado count * sizeof(uint32_t)
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline uint32_t getCount() const { return m_Count; };

	void setIndices(const void* data, uint32_t count);
	void updateIndices(const void* data, uint32_t count);

private:
	uint32_t m_RendererID;
	uint32_t m_Count;

	static IndexBuffer m_DefaultIBO;
};

