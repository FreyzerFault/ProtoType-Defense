#pragma once
#include "glm.hpp"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

class Sprite
{
public:
	// Por defecto = Centro de la ventana 10x10
	Sprite();
	Sprite(uint32_t texID);
	Sprite(glm::vec3 position, float scale, float rotation, uint32_t textureID);
	Sprite(const Sprite& orig);
	Sprite& operator=(const Sprite& orig);
	~Sprite() = default;

	void setTransformation(glm::vec3 position, float scale, float rotation);
	void setPosition(glm::vec3 position) { m_Position = position; }
	void setScale(const float scale) { m_Scale = scale; }
	void setRotation(const float rotation) { m_Rotation = rotation; }

	uint32_t getTexID() const { return m_TextureID; }
	glm::vec3 getPosition() const { return  m_Position; }
	float getRotation() const { return  m_Rotation; }
	float getScale() const { return  m_Scale; }

	glm::mat4 getModelMatrix() const;


private:
	uint32_t m_TextureID;

	glm::vec3 m_Position;
	float m_Scale;
	float m_Rotation; // In radians

};

