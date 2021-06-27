#pragma once
#include "pch.h"

#include "VertexArray.h"
#include "IndexBuffer.h"

// Grid drawable for seeing the hitbox surrounding edges
class HitboxGrid
{
public:

	struct VertexSimple
	{
		float position[3];
		float color[4];
	};
	
	VertexSimple m_Vertices[4];
	unsigned int m_indices[4];
	VertexArray VAO;
	VertexBuffer VBO;
	IndexBuffer IBO;
	VertexBufferLayout layout;
	
	HitboxGrid()
		: m_Vertices{
			{{-0.5f, -0.5f, 5.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
			{{+0.5f, -0.5f, 5.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
			{{+0.5f, +0.5f, 5.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
			{{-0.5f, +0.5f, 5.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
		},
		m_indices{ 0, 1, 2, 3 },
		VBO(m_Vertices, sizeof(VertexSimple) * 4),
		IBO(m_indices, 4)
	{		
		layout.Push<float>(3);
		layout.Push<float>(4);
		VAO.addBuffer(VBO, layout);
	}
};
