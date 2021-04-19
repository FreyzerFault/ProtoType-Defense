#include "Renderer.h"

#include "GlobalParameters.h"
#include "GLDebugging.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include "Sprite.h"
#include "HitboxGrid.h"

using namespace glm;



Renderer::Renderer()
{
	
}

Renderer::~Renderer() = default;

void Renderer::clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::setClearColor(vec3 color)
{
	GLCall(glClearColor(color.r, color.g, color.b, 1.0f));
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, GLenum mode)
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	glPointSize(5.0f);

	GLCall(glDrawElements(mode, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	
	GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::draw(const VertexArray& va, const Shader& shader)
{
	shader.Bind();
	va.Bind();
	IndexBuffer IBO(triangularQuadIndices, 6);
	IBO.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, IBO.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::draw(Sprite& sprite, const Shader& shader)
{
	shader.Bind();
	sprite.bind(); // VAO.Bind() del Sprite
	sprite.getIBO().Bind();

	GLCall(glDrawElements(GL_TRIANGLES, sprite.getIBO().getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::draw(HitboxGrid& grid, const Shader& shader)
{
	shader.Bind();
	grid.VAO.Bind(); // VAO.Bind() del Sprite
	grid.IBO.Bind();
	glPointSize(5.0f);
	GLCall(glDrawElements(GL_POINTS, grid.IBO.getCount(), GL_UNSIGNED_INT, nullptr));
}


// Enable OpenGL Flags like Blending, Textures,...
void Renderer::glEnableFlags()
{
	// ERROR DEBUGGING (automatized what GLCALL() macro, deprecated)
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	// BLENDING:
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // src * alpha + destination * (1 - alpha)

	glEnable(GL_POINT_SMOOTH);
}
