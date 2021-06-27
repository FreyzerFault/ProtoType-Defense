#pragma once
#include "pch.h"

#include "VertexArray.h"
#include "IndexBuffer.h"

// Grid drawable for seeing the hitbox surrounding edges
class SpriteModel
{
public:

	struct SpriteVertex {
		float position[3];
		float color[4];
		float texCoords[2];
		float texIndex;
	};

	SpriteVertex vertices[4];
	unsigned int indices[6];
	VertexArray VAO;
	VertexBuffer VBO;
	IndexBuffer IBO;
	VertexBufferLayout layout;

	SpriteModel() : SpriteModel(0){}

	SpriteModel(uint32_t texID)
		: vertices{
			{{-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, (float)texID},
			{{+0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, (float)texID},
			{{+0.5f, +0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, (float)texID},
			{{-0.5f, +0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, (float)texID},
		},
		indices{
			0, 1, 2,
			2, 3, 0,
		},
		VBO(vertices, sizeof(SpriteVertex) * 4),
		IBO(indices, 6)
	{

		layout.Push<float>(3);	// POSITION
		layout.Push<float>(4);	// COLOR
		layout.Push<float>(2);	// TEXCOORDS
		layout.Push<float>(1);	// TEXID
		VAO.addBuffer(VBO, layout);
	}

	SpriteModel(const SpriteModel& orig) = delete;
};
