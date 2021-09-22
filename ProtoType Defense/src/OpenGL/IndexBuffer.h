#pragma once
#include "pch.h"

class IndexBuffer
{
public:
	IndexBuffer();
	IndexBuffer(const GLuint* data, GLuint count, GLuint type = GL_STATIC_DRAW);
	IndexBuffer(GLuint count); // Buffer de indices vacio con espacio reservado count * sizeof(GLuint)
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	GLuint getCount() const { return m_Count; }

	void setIndices(const void* data, GLuint count);
	void updateIndices(const void* data, GLuint count);

private:
	GLuint m_RendererID;
	GLuint m_Count;

	static IndexBuffer m_DefaultIBO;
};

