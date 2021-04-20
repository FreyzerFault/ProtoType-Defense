#include "Sprite.h"

#include "DefaultStructures.h"
#include "GlobalParameters.h"


Sprite::Sprite() // Por defecto, centrado en la ventana
	: Sprite(glm::vec3(windowCenterX,windowCenterY,0.0f), 1.0f, 0.0f, 0)
{
}

Sprite::Sprite(const uint32_t texID) // Por defecto, centrado en la ventana
	: Sprite(glm::vec3(windowCenterX, windowCenterY, 0.0f), 1.0f, 0.0f, texID)
{
}

Sprite::Sprite(const glm::vec3 position, const float scale, const float rotation, uint32_t textureID)
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


void Sprite::setTransformation(const glm::vec3 position, const float scale, const float rotation)
{
	m_Position = position;
	m_Scale = scale;
	m_Rotation = rotation;
}

glm::mat4 Sprite::getModelMatrix() const
{
	glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Position);
	model = glm::rotate(model, m_Rotation, glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(m_Scale, m_Scale, 0));
	return model;
}



