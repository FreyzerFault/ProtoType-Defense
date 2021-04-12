#pragma once

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Sprite.h"

class Renderer
{
	static const float defaultClearColor[3];
private:
	IndexBuffer m_DefaultIBO;
public:
	Renderer();
	~Renderer();

	static void clear();
	static void setClearColor(const float* color = defaultClearColor);

	// Generic VAO Drawing
	static void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

	// Sprite Drawing
	void draw(Sprite& sprite, const Shader& shader) const;
};