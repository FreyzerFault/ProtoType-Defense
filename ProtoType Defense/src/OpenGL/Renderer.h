#pragma once
#include "pch.h"

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

	// Clear Buffers
	static void clear();

	// Background Color
	static void setClearColor(glm::vec3 color = defaultBackgroundColor);
	

	// MODEL VIEW PROJECTION Matrix
	void setMVP(const glm::mat4& mvp) { defaultMVP = mvp; }
	glm::mat4 getMVP() const { return defaultMVP; }

	TextureManager& getTextureManager() { return textureManager; }
	ShaderManager& getShaderManager() { return shaderManager; }


	// DRAWCALLS
	
	// Use VAO+IBO
	void draw(const VertexArray& va, const IndexBuffer& ib, const std::string& shaderName = "NoTexture", glm::mat4 mvp = glm::mat4(0.0f), GLenum mode = GL_TRIANGLES);

	// Use Raw vertex and index data
	template <typename T>
	void draw(const void* vertices, uint32_t vertexCount, uint32_t* indices, uint32_t indexCount, const std::string& shaderName = "NoTexture", glm::mat4 mvp = glm::mat4(0.0f), GLenum mode = GL_TRIANGLES);

	// Sprite Quad
	void draw(Sprite& sprite);

	// Hitbox Quad
	void draw(const Hitbox& hitbox);

	// Quad
	template <typename T>
	void drawQuad(const void* vertices, const std::string& shaderName = "NoTexture", glm::mat4 mvp = glm::mat4(0.0f));
	template <typename T>
	void drawQuadBorder(const void* vertices, const std::string& shaderName = "NoTexture", glm::mat4 mvp = glm::mat4(0.0f));

	// Circle
	void drawCircle(glm::vec3 center, float radius, int segments, glm::vec4 color);
	void drawCircumference(glm::vec3 center, float radius, int segments, glm::vec4 color, int lineWidth = 5);



	// Activate OpenGL Tools like Blending, Culling...
	static void glEnableFlags();
	

	
	// Fill the VAO with a new VBO
	template <typename T>
	VertexArray& fillVAO(VertexArray& vao, VertexBufferLayout& layout, const void* vertices, uint32_t count, GLenum drawType = GL_STATIC_DRAW);
	static VertexArray& fillVAO(VertexArray& vao, VertexBuffer& vbo, VertexBufferLayout& layout);

	// Fill the IBO with indices
	IndexBuffer& fillIBO(uint32_t* indices, uint32_t count, GLenum drawType = GL_STATIC_DRAW);
	

private:

	glm::mat4 defaultMVP;
	
	std::map<int, SpriteModel> spriteModels;
	HitboxGrid hitboxGrid;

	TextureManager textureManager;
	ShaderManager shaderManager;

	//Temporal use Objects
	std::shared_ptr<VertexArray> tmpVAO;
	std::shared_ptr<VertexBuffer> tmpVBO;
	std::shared_ptr<IndexBuffer> tmpIBO;
};

template <typename T>
void Renderer::draw(const void* vertices, uint32_t vertexCount, uint32_t* indices, uint32_t indexCount,
	const std::string& shaderName, glm::mat4 mvp, GLenum mode)
{
	// No texture
	shaderManager.Bind(shaderName);
	VertexBufferLayout& layout = shaderManager.getShader().getLayout();

	// Inicializa VAO
	tmpVAO = std::make_shared<VertexArray>();
	VertexArray& vao = fillVAO<T>(*tmpVAO, layout, vertices, vertexCount);

	IndexBuffer& ibo = fillIBO(indices, indexCount);

	draw(vao, ibo, shaderName, mvp, mode);
}

template <typename T>
void Renderer::drawQuad(const void* vertices, const std::string& shaderName, glm::mat4 mvp)
{
	uint32_t indices[6]{
		0, 1, 2,
		2, 3, 0,
	};

	draw<T>(vertices, 4, &indices[0], 6, shaderName, mvp);
}

template <typename T>
void Renderer::drawQuadBorder(const void* vertices, const std::string& shaderName, glm::mat4 mvp)
{
	uint32_t indices[4]{
		0, 1, 2, 3
	};
	const IndexBuffer ibo(indices, 4);

	draw<T>(vertices, 4, indices, 4, shaderName, mvp, GL_LINES);
}

template <typename T>
VertexArray& Renderer::fillVAO(VertexArray& vao, VertexBufferLayout& layout, const void* vertices, uint32_t count, GLenum drawType)
{
	tmpVBO = std::make_shared<VertexBuffer>(vertices, count * sizeof(T), drawType);
	
	return fillVAO(vao, *tmpVBO, layout);
}
