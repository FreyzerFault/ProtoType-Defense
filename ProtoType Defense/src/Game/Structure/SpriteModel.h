#pragma once
#include "pch.h"

#include "VertexArray.h"
#include "IndexBuffer.h"

// Grid drawable for seeing the hitbox surrounding edges
class SpriteModel
{
public:

	struct SpriteVertex {
		GLfloat position[3];
		GLfloat color[4];
		GLfloat texCoords[2];
		GLint texIndex; // Tex Index can be -1 (No Texture)
	};

	SpriteVertex vertices[4];
	GLuint indices[6];
	VertexArray VAO;
	VertexBuffer VBO;
	IndexBuffer IBO;
	VertexBufferLayout layout;

	SpriteModel() : SpriteModel(0){}

	SpriteModel(GLint texID)
		: vertices{
			{{-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, texID},
			{{+0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, texID},
			{{+0.5f, +0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, texID},
			{{-0.5f, +0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, texID},
		},
		indices{
			0, 1, 2,
			2, 3, 0,
		},
		VBO(vertices, sizeof(SpriteVertex) * 4),
		IBO(indices, 6)
	{

		layout.Push<GLfloat>(3);	// POSITION
		layout.Push<GLfloat>(4);	// COLOR
		layout.Push<GLfloat>(2);	// TEXCOORDS
		layout.Push<GLint>(1);	// TEXID
		VAO.addBuffer(VBO, layout);
	}

	SpriteModel(const SpriteModel& orig) = delete;
};
