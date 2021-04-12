#pragma once
#include "glm.hpp"
#include "VertexArray.h"
#include "VertexBuffer.h"

struct Vertex {
	float position[3];
	float color[4];
	float texCoords[2];
	float texIndex;
};

class Sprite
{

private:
	Vertex m_Vertices[4];
	unsigned int m_TextureID;

	glm::vec3 m_Position;
	float m_Scale;
	float m_Rotation; // In º

	VertexArray m_VAO;
	VertexBuffer m_VBO;

public:
	// Por defecto = Centro de la ventana 10x10
	Sprite();
	Sprite(unsigned int texID);
	Sprite(glm::vec3 position, float scale, float rotation, unsigned int textureID);
	Sprite(const Sprite& orig);
	Sprite& operator=(const Sprite& orig);
	~Sprite();

	void setTransformation(glm::vec3 position, float scale, float rotation);
	void setPosition(glm::vec3 position) { m_Position = position; };
	void setScale(const float scale) { m_Scale = scale; };
	void setRotation(const float rotation) { m_Rotation = rotation; };

	unsigned int getTexID() const { return m_TextureID; };

	glm::mat4 getModelMatrix() const;

	void bind() const; // VAO.Bind() (used on Renderer)
};

