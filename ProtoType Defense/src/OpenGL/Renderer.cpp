#include "Renderer.h"

#include "GlobalParameters.h"
#include "GLDebugging.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "ShaderManager.h"

#include "Structure/Sprite.h"
#include "Structure/HitboxGrid.h"
#include "Structure/Hitbox.h"

using namespace glm;

Renderer::Renderer() = default;

Renderer::Renderer(const int numTextures)
{
	// SpriteModels (texID)
	for (int i = 0; i < numTextures; ++i)
	{
		spriteModels.try_emplace(i, i);
	}

	// SHADERS
	shaderManager.add("NoTexture");
	shaderManager.add("Basic");
	// MAX Texture Slots
	shaderManager.setTextureSlots(numTextures);
	
	// TEXTURAS
	for (int i = 0; i < numTextures; i++)
	{
		textureManager.add(std::to_string(i), i);
		std::cout << "Added texture " << textureManager.getTextureName(i) << " to Slot " << i << std::endl;
	}
	for (int i = 0; i < numTextures; i++)
	{
		textureManager.Bind(std::to_string(i), i);
	}
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

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const std::string& shaderName, GLenum mode)
{
	shaderManager.Bind(shaderName);
	va.Bind();
	ib.Bind();

	shaderManager.setUniformMat4f("u_MVP", defaultMVP);

	GLCall(glDrawElements(mode, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const std::string& shaderName)
{
	shaderManager.Bind(shaderName);
	va.Bind();
	ib.Bind();

	shaderManager.setUniformMat4f("u_MVP", defaultMVP);

	GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::draw(const VertexArray& va, const std::string& shaderName)
{
	shaderManager.Bind(shaderName);
	va.Bind();
	const IndexBuffer IBO(triangularQuadIndices, 6);
	IBO.Bind();

	shaderManager.setUniformMat4f("u_MVP", defaultMVP);

	GLCall(glDrawElements(GL_TRIANGLES, IBO.getCount(), GL_UNSIGNED_INT, nullptr));
}


void Renderer::draw(const Sprite& sprite)
{
	shaderManager.Bind("Basic");
	
	spriteModels.at(sprite.getTexID()).VAO.Bind();
	spriteModels.at(sprite.getTexID()).IBO.Bind();
	
	shaderManager.setUniformMat4f("u_MVP", defaultMVP * sprite.getModelMatrix());

	GLCall(glDrawElements(GL_TRIANGLES, spriteModels.at(sprite.getTexID()).IBO.getCount(), GL_UNSIGNED_INT, nullptr));
}


void Renderer::draw(const Hitbox& hitbox)
{
	shaderManager.Bind("NoTexture");
	
	hitboxGrid.VAO.Bind();
	hitboxGrid.IBO.Bind();
	
	shaderManager.setUniformMat4f("u_MVP", defaultMVP * hitbox.getModelMatrix());
	
	GLCall(glDrawElements(GL_LINE_LOOP, hitboxGrid.IBO.getCount(), GL_UNSIGNED_INT, nullptr));
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

	//glEnable(GL_POINT_SMOOTH);
}
