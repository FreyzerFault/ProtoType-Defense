#pragma once
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "DefaultStructures.h"

#include "TextureManager.h"
#include "ShaderManager.h"

#include "Structure/SpriteModel.h"
#include "Structure/HitboxGrid.h"

class Hitbox;
class VertexArray;
class Shader;
class Sprite;

class Renderer
{
public:
	Renderer();
	Renderer(const int numTextures);
	~Renderer();


	static void clear();
	static void setClearColor(glm::vec3 color = defaultClearColor);

	void setMVP(const glm::mat4& mvp) { defaultMVP = mvp; }
	glm::mat4 getMVP() const { return defaultMVP; }

	// Generic VAO Drawing
	static void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, GLenum mode);
	static void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	static void draw(const VertexArray& va, const Shader& shader); // with Default IBO

	// Sprite Drawing
	void draw(const Sprite& sprite);

	// Hitbox Grid Drawing
	void draw(const Hitbox& hitbox);


	static void glEnableFlags();

private:

	glm::mat4 defaultMVP;
	
	std::map<int, SpriteModel> spriteModels;
	HitboxGrid hitboxGrid;

	TextureManager textureManager;
	ShaderManager shaderManager;
	
};