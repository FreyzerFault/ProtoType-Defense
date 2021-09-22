#include "pch.h"
#include "Sprite.h"

#include "GlobalParameters.h"

using namespace glm;

Sprite::Sprite() // Por defecto, centrado en la ventana
	: Sprite(glm::vec3(windowCenterX,windowCenterY, 1.0f), vec2(1.0f), 0.0f, 0)
{
}

Sprite::Sprite(const GLuint texID) // Por defecto, centrado en la ventana
	: Sprite(glm::vec3(windowCenterX, windowCenterY, 0.0f), vec2(1.0f), 0.0f, texID)
{
}

Sprite::Sprite(const glm::vec3 position, vec2 scale, const GLfloat rotation, GLuint textureID)
	: m_TextureID(textureID), m_Position(position), m_Scale(scale), m_Rotation(rotation)
{
}

Sprite::Sprite(const Sprite& orig)
	: Sprite(orig.m_Position, orig.m_Scale, orig.m_Rotation, orig.m_TextureID)
{
}

// Copia los vertices y textura pero mantiene su posicion, rotacion y escalado
Sprite& Sprite::operator=(const Sprite& orig)
{
	if (&orig != this)
	{
		this->m_TextureID = orig.m_TextureID;
	}
	return *this;
}


void Sprite::setTransformation(const glm::vec3 position, const vec2 scale, const GLfloat rotation)
{
	m_Position = position;
	m_Scale = scale;
	m_Rotation = rotation;
}

void Sprite::setRelativeScale(GLfloat width, GLfloat height)
{
	if (width > height)
		m_Scale = vec2(m_Scale.x, m_Scale.y * height / width);
	else
		m_Scale = vec2(m_Scale.y * width / height, m_Scale.y);
}

glm::mat4 Sprite::getModelMatrix() const
{
	mat4 model = translate(glm::mat4(1.0f), m_Position);
	model = rotate(model, m_Rotation, vec3(0, 0, 1));
	model = scale(model, vec3(m_Scale, 0));
	return model;
}



