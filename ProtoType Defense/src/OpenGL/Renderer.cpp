#include "pch.h"
#include "Renderer.h"

#include "GLDebugging.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderManager.h"

#include "Structure/Sprite.h"
#include "Structure/HitboxGrid.h"
#include "Structure/Hitbox.h"

using namespace glm;

Renderer::Renderer() = default;

Renderer::Renderer(const int numTextures)
	: defaultMVP(1.0f)
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
	
	// TEXTURES
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
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::setClearColor(vec3 color)
{
	GLCall(glClearColor(color.r, color.g, color.b, 1.0f));
}

// Specify PRIMITIVE in [mode]
void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const std::string& shaderName, glm::mat4 mvp, GLenum mode)
{
	shaderManager.Bind(shaderName);
	va.Bind();
	ib.Bind();
	
	if (mvp == mat4(0.0f))
		mvp = defaultMVP;
	
	shaderManager.setUniformMat4f("u_MVP", mvp);

	GLCall(glDrawElements(mode, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}


// SPRITE
void Renderer::draw(Sprite& sprite)
{
	SpriteModel& model = spriteModels.at(sprite.getTexID());

	// Adjust scale to the texture
	textureManager.Bind(std::to_string(sprite.getTexID()), sprite.getTexID());
	if (sprite.getScale().x == sprite.getScale().y && textureManager.getTexture().getWidth() != textureManager.getTexture().getHeight())
		sprite.setRelativeScale(textureManager.getTexture().getWidth(), textureManager.getTexture().getHeight());
	
	draw(model.VAO, model.IBO, "Basic", defaultMVP * sprite.getModelMatrix());
}

// HITBOX
void Renderer::draw(const Hitbox& hitbox)
{
	draw(hitboxGrid.VAO, hitboxGrid.IBO, "NoTexture", defaultMVP * hitbox.getModelMatrix(), GL_LINE_LOOP);
}


// CIRCLE
void Renderer::drawCircle(glm::vec3 center, GLfloat radius, int segments, vec4 color)
{
	std::vector<HitboxGrid::VertexSimple> vertices(segments + 1); // Center + Circle

	std::vector<GLuint> indices(segments * 3); // {center, vertex, vertex+1}

	const HitboxGrid::VertexSimple centerVertex = { {center.x, center.y, center.z}, {color.x, color.y, color.z, color.w} };

	vertices[0] = centerVertex;
	
	for (int i = 1; i <= segments; i++) {

		const GLfloat angle = 2.0f * 3.1415926f * (GLfloat)i / (GLfloat)segments;
		const GLfloat x = radius * cosf(angle);
		const GLfloat y = radius * sinf(angle);

		// VERTICES
		vertices[i] = { {x + center.x, y + center.y, center.z}, {color.x, color.y, color.z, color.w} };

		// INDICES
		indices[(i - 1) * 3 + 0] = 0; // Center
		indices[(i-1) * 3 + 1] = i;
		if (i == segments)
			indices[(i - 1) * 3 + 2] = 1;
		else
			indices[(i - 1) * 3 + 2] = i+1;
	}

	draw<HitboxGrid::VertexSimple>(&vertices[0], segments + 1, &indices[0], segments * 3, "NoTexture");
}

void Renderer::drawCircumference(glm::vec3 center, GLfloat radius, int segments, vec4 color, int lineWidth)
{
	std::vector<HitboxGrid::VertexSimple> vertices(segments);

	std::vector<GLuint> indices(segments);

	for (int i = 0; i < segments; i++) {

		const GLfloat angle = 2.0f * 3.1415926f * (GLfloat)i / (GLfloat)segments;
		const GLfloat x = radius * cosf(angle);
		const GLfloat y = radius * sinf(angle);

		// VERTICES
		vertices[i] = { {x + center.x, y + center.y, center.z}, {color.x, color.y, color.z, color.w} };

		// INDICES
		indices[i] = i;
	}
	
	glLineWidth(lineWidth);
	
	draw<HitboxGrid::VertexSimple>(&vertices[0], segments, &indices[0], segments, "NoTexture", defaultMVP, GL_LINE_LOOP);
	
	// Reset LineWidth
	glLineWidth(1);
}


VertexArray& Renderer::fillVAO(VertexArray& vao, VertexBuffer& vbo, VertexBufferLayout& layout)
{
	vao.addBuffer(vbo, layout);
	return vao;
}

IndexBuffer& Renderer::fillIBO(GLuint* indices, GLuint count, GLenum drawType)
{
	tmpIBO = std::make_shared<IndexBuffer>(indices, count, drawType);

	return *tmpIBO;
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
	
	// Z-BUFFER DEPTH TEST
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_POINT_SMOOTH);
}
