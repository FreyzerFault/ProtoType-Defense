#pragma once
#include "pch.h"

class Sprite
{
public:
	// Por defecto = Centro de la ventana 10x10
	Sprite();
	Sprite(GLuint texID);
	Sprite(glm::vec3 position, glm::vec2 scale, GLfloat rotation, GLuint textureID);
	Sprite(const Sprite& orig);
	Sprite& operator=(const Sprite& orig);
	~Sprite() = default;

	void setTransformation(glm::vec3 position, const glm::vec2 scale, GLfloat rotation);
	void setPosition(glm::vec3 position) { m_Position = position; }
	void setScale(const glm::vec2 scale) { m_Scale = scale; }
	void setRotation(const GLfloat rotation) { m_Rotation = rotation; }

	// Set Scale to a Resolution width:height, 1:0.f
	void setRelativeScale(GLfloat width, GLfloat height);

	GLuint getTexID() const { return m_TextureID; }
	glm::vec3 getPosition() const { return  m_Position; }
	GLfloat getRotation() const { return  m_Rotation; }
	glm::vec2 getScale() const { return  m_Scale; }

	glm::mat4 getModelMatrix() const;


private:
	GLuint m_TextureID;

	glm::vec3 m_Position;
	glm::vec2 m_Scale;
	GLfloat m_Rotation; // In radians

};

