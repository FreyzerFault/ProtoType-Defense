#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "IndexBuffer.h"
#include "DefaultStructures.h"

class HitboxGrid;
class VertexArray;
class Shader;
class Sprite;

class Renderer
{
public:
	Renderer();
	~Renderer();


	static void clear();
	static void setClearColor(glm::vec3 color = defaultClearColor);

	// Generic VAO Drawing
	static void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, GLenum mode);
	static void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

	// VAO Drawing with Default IBO
	static void draw(const VertexArray& va, const Shader& shader);

	// Sprite Drawing
	static void draw(Sprite& sprite, const Shader& shader);

	// Hitbox Grid Drawing
	static void draw(HitboxGrid& grid, const Shader& shader);


	static void glEnableFlags();
	
};