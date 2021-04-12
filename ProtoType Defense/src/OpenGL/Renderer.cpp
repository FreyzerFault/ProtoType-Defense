#include "Renderer.h"
#include "GLDebugging.h"

const float Renderer::defaultClearColor[3] = { 0.1f, 0.1f, 0.15f };

static unsigned int indices[6]{ // Indices de un Quad
	0, 1, 2,
	2, 3, 0,
};

Renderer::Renderer()
	: m_DefaultIBO(indices, 6)
{
	
}

Renderer::~Renderer() = default;

void Renderer::clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::setClearColor(const float* color)
{
	GLCall(glClearColor(color[0], color[1], color[2], 1.0f));
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	
	GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::draw(Sprite& sprite, const Shader& shader) const
{
	shader.Bind();
	sprite.bind(); // VAO.Bind() del Sprite
	m_DefaultIBO.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, m_DefaultIBO.getCount(), GL_UNSIGNED_INT, nullptr));
}
