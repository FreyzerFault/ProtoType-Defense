#pragma once
#include <glm.hpp>

static glm::vec3 defaultBackgroundColor( 0.1f, 0.1f, 0.1f );

static glm::vec3 colorPath(0.3f);					// Path		Tile Color
static glm::vec3 colorPlatform(0.1f, 0.1f, 0.15f);	// Platform	Tile Color
static glm::vec3 colorTile(0.1f);					// Default	Tile Color

static uint32_t triangularQuadIndices[6]{ // Indices de un Quad
	0, 1, 2,
	2, 3, 0,
};

static uint32_t QuadIndices[4]{ // Indices de un Quad
	0, 1, 2, 3
};


