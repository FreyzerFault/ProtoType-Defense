#pragma once
#include "pch.h"

#include "Structure/Entity.h"
#include "Objects/Tower.h"

class Projectile : public Entity
{
	// BASE STATS
	static const float baseOrientation; // = 0.0f

public:
	Projectile(const Tower* tower);

	// 2D
	Projectile(const Tower* tower, glm::vec2 position, glm::vec2 size = glm::vec2(8.0f),
		float orientation = 0.0f, bool homming = false);
	// 3D Flat Hitbox
	Projectile(const Tower* tower, glm::vec3 position, glm::vec2 size = glm::vec2(8.0f),
		float orientation = 0.0f, bool homming = false);
	// 3D
	Projectile(const Tower* tower, glm::vec3 position, glm::vec3 size,
		float orientation = 0.0f, bool homming = false);

	Projectile(const Projectile& orig);
	~Projectile() override;

	Projectile& operator=(const Projectile& orig);

	
	int getPierce() const { return m_Pierce; }
	bool getHomming() const { return m_Homming; }
	void setHomming(bool hom) { m_Homming = hom; }

	
	bool impact(Hitbox& hitbox);
	Enemy* impact(std::list<Enemy>& enemies);

	
	void move(const float d) override;
	
private:
	
	int m_Pierce; // Nº Enemies that can pierce until it disapears
	bool m_Homming;

	const Tower* m_Tower;

	// Helps to detect only the first impact for every hitbox
	std::list<Hitbox*> impacted;
};

