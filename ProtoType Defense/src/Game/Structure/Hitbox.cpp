#include "Hitbox.h"

#include <algorithm>

#include "GlobalParameters.h"

using namespace glm;

#define pX m_Position[0]
#define pY m_Position[1]
#define pZ m_Position[2]
#define sX m_Size[0]
#define sY m_Size[1]
#define sZ m_Size[2]

Hitbox::Hitbox()
	: Hitbox(vec2(windowCenterX, windowCenterY), vec2(16.0f))
{
}

Hitbox::Hitbox(vec2 position, vec2 size, float yaw)
	: Hitbox(vec3(position, 0.0f), vec3(size, 0.0f), yaw)
{
}

Hitbox::Hitbox(vec3 position, vec3 size, float yaw)
	: m_Position(position), m_Size(size), m_Yaw(yaw),
	vertices{
		vec2(pX - sX/2, pY - sY/2),
		vec2(pX + sX/2, pY - sY/2),
		vec2(pX + sX/2, pY + sY/2),
		vec2(pX - sX/2, pY + sY/2),
	}
{
}


bool Hitbox::collision(Hitbox& object)
{
	// If the Entity is rotated, solution isn't trivial, SAT algorithm needed
	if (m_Yaw != 0) SATcollision(object);

	// Trivial solution
	
	const float o_X = object.getX(), o_Y = object.getY(), o_Z = object.getZ();
	const float o_sX = object.getsX(), o_sY = object.getsY(), o_sZ = object.getsZ();
	
	bool const collide =
		// X axis
		(pX		< o_X + o_sX)	&&
		(o_X	< pX + sX)		&&
		(pY		< o_Y + o_sY)	&&
		(o_Y	< pY + sY);
	return collide;
}

// This algorithm can work with all type of Convexe Polygons, but it's modified for rectangle so it's more efficient
bool Hitbox::SATcollision(Hitbox& object)
{
	Hitbox* hb1 = this;
	Hitbox* hb2 = &object;
	updateVertices();
	hb2->updateVertices();

	for (int i = 0; i < 2; i++)
	{
		// Swap hitboxes
		if (i == 2)
		{
			hb1 = hb2;
			hb2 = hb1;
		}

		// SAT Algorithm (but only 2 edges, it's a rectangle)
		vec2 p = hb1->vertices[0];  // -x -y
		vec2 a = hb1->vertices[1]; // +x -y
		vec2 b = hb1->vertices[3]; // -x +y

		// Edge 1 = p -> a, Edge 2 = p -> b
		// Axis Projector perpendicular to the edge (-y,x) (no sirve pa na porque es un rectangulo)
		const vec2 axisProj[2] = {
			vec2(-(a.y - p.y), a.x - p.x),
			vec2(-(b.y - p.y), b.x - p.x)
		};

		for (vec2 axis : axisProj)
		{
			// Min & Max Projected vertices
			float min1 = INFINITY, max1 = -INFINITY;
			float min2 = INFINITY, max2 = -INFINITY;
			// First Hitbox
			for (vec2 p : hb1->vertices)
			{
				// Projection point of the vertex over the axis vector (p0,p1) over (-y,x) vector
				float q = (p.x * axis.x + p.y * axis.y);
				min1 = std::min(min1, q);
				max1 = std::max(max1, q);
			}
			// Second Hitbox
			for (vec2 p : hb2->vertices)
			{
				// Projection point of the vertex over the axis vector (p0,p1) over (-y,x) vector
				float q = (p.x * axis.x + p.y * axis.y);
				min1 = std::min(min1, q);
				max1 = std::max(max1, q);
			}

			// Si las proyecciones no se solapan en minimo 1 axis, no hay colision
			if (!(max2 >= min1 && max1 >= min2))
				return false;
		}
	}
	
	return false;
}

void Hitbox::updateVertices()
{
	vertices[0] = vec2(pX - sX / 2 * cos(m_Yaw), pY - sY / 2 * sin(m_Yaw));
	vertices[1] = vec2(pX + sX / 2 * cos(m_Yaw), pY - sY / 2 * sin(m_Yaw));
	vertices[2] = vec2(pX + sX / 2 * cos(m_Yaw), pY + sY / 2 * sin(m_Yaw));
	vertices[3] = vec2(pX - sX / 2 * cos(m_Yaw), pY + sY / 2 * sin(m_Yaw));
}


void Hitbox::move(const float X, const float Y, const float Z)
{
	pX += X;
	pY += Y;
	pZ += Z;
}

void Hitbox::move(const float d)
{
	pX += d * cos(m_Yaw);
	pY += d * sin(m_Yaw);
}

void Hitbox::rotate(float X)
{
	m_Yaw += rad(X);
	// Normalized to [0,2PI] radians
	m_Yaw -= floor(m_Yaw / (2 * PI)) * 2 * PI;
}

mat4 Hitbox::getModelMatrix() const
{
	mat4 model = glm::translate(mat4(1.0f), m_Position);
	model = glm::rotate(model, (float)m_Yaw, glm::vec3(0, 0, 1));
	model = glm::scale(model, vec3(sX/2, sY/2, 1.0f));
	return model;
}
