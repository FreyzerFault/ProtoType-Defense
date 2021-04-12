#include "Projectile.h"

#include <trigonometric.hpp>
#include "GlobalParameters.h"

Projectile::Projectile()
	: Projectile(windowCenterX, windowCenterY, 10.0f, 10.0f, 0.0f, 1, false)
{
}

// 2D
Projectile::Projectile(const float X, const float Y, const float sX, const float sY,
	float orientation, const int piercing, bool homming)
	: Entity(X, Y, sX, sY), orientation(orientation), pierce(piercing), homming(homming)
{
}

// 3D
Projectile::Projectile(const float X, const float Y, const float Z,
	const float sX, const float sY, const float sZ,
	float orientation, const int piercing, bool homming)
	: Entity(X,Y,Z, sX, sY, sZ), orientation(orientation), pierce(piercing), homming(homming)
{
}


Projectile::Projectile(const Projectile& orig) = default;

Projectile::~Projectile() = default;


void Projectile::move(const float distance)
{
	Entity::move(distance * glm::cos(orientation), distance * glm::sin(orientation), 0.0f);
}

bool Projectile::Impact()
{
	// IF Piercing:
	pierce--;

	// If piercing stop pursuing and goes straight
	homming = false;

	return true;
}




