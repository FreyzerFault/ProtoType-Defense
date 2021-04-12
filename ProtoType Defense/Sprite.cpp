#include "Sprite.h"
#include "GlobalParameters.h"
#include "gtc/matrix_transform.hpp"

// INITIAL PARAMETERS
static float iniPosition[3]{ 0.0f, 0.0f, 0.0f };
static float iniSize = 16.0f;

Sprite::Sprite() // Por defecto, centrado en la ventana
	: Sprite(glm::vec3(windowCenterX,windowCenterY,0.0f), 1.0f, 0.0f, 0)
{
}

Sprite::Sprite(const unsigned int texID) // Por defecto, centrado en la ventana
	: Sprite(glm::vec3(windowCenterX, windowCenterY, 0.0f), 1.0f, 0.0f, texID)
{
}

Sprite::Sprite(const glm::vec3 position, const float scale, const float rotation, unsigned int textureID)
	: m_Vertices{
		{{iniPosition[0],				iniPosition[1],				iniPosition[2]}, {0.0f,0.0f,0.0f,0.0f}, {0.0f, 1.0f}, (float)textureID},
		{{iniPosition[0] + iniSize,		iniPosition[1],				iniPosition[2]}, {0.0f,0.0f,0.0f,0.0f}, {1.0f, 1.0f}, (float)textureID},
		{{iniPosition[0] + iniSize,		iniPosition[1] + iniSize,	iniPosition[2]}, {0.0f,0.0f,0.0f,0.0f}, {1.0f, 0.0f}, (float)textureID},
		{{iniPosition[0],				iniPosition[1] + iniSize,	iniPosition[2]}, {0.0f,0.0f,0.0f,0.0f}, {0.0f, 0.0f}, (float)textureID},
	  },
	m_TextureID(textureID), m_Position(position), m_Scale(scale),
	m_Rotation(rotation),
	m_VBO(m_Vertices, sizeof(Vertex) * 4 /*GL_STATIC_DRAW*/)
{	
	m_VAO.setDefaultBuffer(m_VBO); // Default = 3D RGBA Tex2D texID
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
		memcpy(this->m_Vertices, orig.m_Vertices, sizeof(Vertex) * 4);
		this->m_VBO.updateData(this->m_Vertices, sizeof(Vertex) * 4);
		m_VAO.setDefaultBuffer(m_VBO);
		
		this->m_TextureID = orig.m_TextureID;
	}
	return *this;
}

Sprite::~Sprite() = default;

void Sprite::setTransformation(const glm::vec3 position, const float scale, const float rotation)
{
	m_Position = position;
	m_Scale = scale;
	m_Rotation = rotation;
}

glm::mat4 Sprite::getModelMatrix() const
{
	glm::mat4 model = glm::translate(glm::mat4(0.1f), m_Position);
	model = glm::rotate(model, rad(m_Rotation), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(m_Scale, m_Scale, 0));
	return model;
}

void Sprite::bind() const
{
	m_VAO.Bind();
}


