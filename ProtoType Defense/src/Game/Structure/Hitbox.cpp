#include "Hitbox.h"

#include <algorithm>

#include "GlobalParameters.h"

using namespace glm;

#define pX position[0]
#define pY position[1]
#define pZ position[2]
#define sX size[0]
#define sY size[1]
#define sZ size[2]

Hitbox::Hitbox()
	: Hitbox(vec2(windowCenterX, windowCenterY), vec2(16.0f, 16.0f))
{
}

Hitbox::Hitbox(vec2 position, vec2 size, float yaw)
	: Hitbox(vec3(position, 0.0f), vec3(size, 0.0f), yaw)
{
}

Hitbox::Hitbox(vec3 position, vec3 size, float yaw)
	: position(position), size(size), yaw(yaw)
{
}


bool Hitbox::collision(Hitbox& object)
{
	// If the Entity is rotated, solution isn't trivial, SAT algorithm needed
	if (yaw != 0) SATcollision(object);

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
	vertices[0] = vec2(pX - sX / 2 * cos(yaw), pY - sY / 2 * sin(yaw));
	vertices[1] = vec2(pX + sX / 2 * cos(yaw), pY - sY / 2 * sin(yaw));
	vertices[2] = vec2(pX + sX / 2 * cos(yaw), pY + sY / 2 * sin(yaw));
	vertices[3] = vec2(pX - sX / 2 * cos(yaw), pY + sY / 2 * sin(yaw));
}


void Hitbox::move(const float X, const float Y)
{
	pX += X * cos(yaw);
	pY += Y * sin(yaw);
}

void Hitbox::move(const float X, const float Y, const float Z)
{
	pX += X * cos(yaw);
	pY += Y * sin(yaw);
	pZ += Z;
}

void Hitbox::rotate(float X)
{
	// Normalized to [0,360] º
	if (X > 360 || X < 0) X -= floor(X / 360) * 360;
	yaw += rad(X);
}