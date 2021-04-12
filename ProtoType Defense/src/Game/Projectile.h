#pragma once

#include "Entity.h"
#include "GlobalStats.h"

class Projectile : public Entity
{
	// BASE STATS
	static const float baseOrientation; // = 0.0f
private:
	
	float orientation; // º with X AXIS
	int pierce; // Nº Enemies that can pierce until it disapears
	bool homming;
	
	void move(const float distance = 1.0f);
	bool Impact();

public:
	Projectile();
	// 2D
	Projectile(const float X, const float Y, const float sX = 10.0f, const float sY = 10.0f,
	           float orientation = 0.0f, const int piercing = 1, bool homming = false);
	// 3D
	Projectile(const float X, const float Y, const float Z = 0.0f, const float sX = 10.0f, const float sY = 10.0f,
	           const float sZ = 0.0f, float orientation = 0.0f, const int piercing = 1, bool homming = false);

	Projectile(const Projectile& orig);

	~Projectile() override;


};

