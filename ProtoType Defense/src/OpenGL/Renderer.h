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
	static void setClearColor(glm::vec3 color = defaultBackgroundColor);

	void setMVP(const glm::mat4& mvp) { defaultMVP = mvp; }
	glm::mat4 getMVP() const { return defaultMVP; }

	// Generic VAO Drawing
	void draw(const VertexArray& va, const IndexBuffer& ib, const std::string& shaderName, GLenum mode);
	void draw(const VertexArray& va, const IndexBuffer& ib, const std::string& shaderName);
	void draw(const VertexArray& va, const IndexBuffer& ib, const std::string& shaderName, uint32_t* ptr);
	void draw(const VertexArray& va, const std::string& shaderName); // with Default IBO

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