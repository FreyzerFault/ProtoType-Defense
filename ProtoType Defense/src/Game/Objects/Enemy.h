#pragma once
#include "pch.h"

#include "HealthBar.h"
#include "Map/Tile.h"
#include "Structure/Entity.h"

class Path;

enum class TypeEnemy
{
	basic,
	tank,
	sneaky,
	flying
};

static std::string typeToString(TypeEnemy& type)
{
	switch (type)
	{
	case TypeEnemy::basic:
		return "Basic";
	case TypeEnemy::tank:
		return "Tank";
	case TypeEnemy::sneaky:
		return "Sneaky";
	case TypeEnemy::flying:
		return "Flying";
	}
	return "";
}

class Enemy: public Entity
{
public:
	

	Enemy(glm::vec3 pos, int texID = 2, double yaw = 0, glm::vec2 spriteScale = glm::vec2(64.0f), int life = baseLife, GLfloat speed = baseSpeed);
	Enemy(Tile& tile, int texID = 2, glm::vec2 spriteScale = glm::vec2(64.0f), int life = baseLife, GLfloat speed = baseSpeed);
	~Enemy() override;

	
	// Hit
	int getHit(GLfloat hitDmg);
	void endHit() { hit = false; }

	
	// Move
	void move(GLfloat d) override;
	void setPosition(glm::vec3 pos) override;

	void slow(GLfloat slowPercentage);
	
	void setTile(Tile* tileOcuppied) { tile = tileOcuppied; }
	Tile* getTile() const { return tile; }


	// True if distance(center, enemy) < range
	bool inRange(glm::vec2 center, GLfloat range) const;
	
	
	// STATS
	int getLife() const { return life; }
	GLfloat getSpeed() const { return speed; }
	int getReward() const { return reward; }
	int getDamage() const { return damage; }
	void setLife(const GLuint l) { life = l; }
	void setSpeed(const GLfloat spd) { speed = spd; }

	// BASE STATS
	static const int baseLife = 500;
	static const int baseSpeed = 50;
	static const GLuint baseReward = 20;
	static const GLuint baseDamage = 1; // User Life loss if scape


	// DRAW
	void draw(Renderer& renderer) const;
	void drawHitbox(Renderer& renderer) const;

private:
	
	Tile* tile;

	HealthBar healthBar;

	int life;
	int iniLife;
	GLfloat speed;
	int reward;
	int damage;

	bool hit = false; // Flag if is was hit this frame
	
	// Frames that lasts the red flash when is hit an enemy
	int framesHitCounter = 20;
};

