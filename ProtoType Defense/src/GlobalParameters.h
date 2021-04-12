#pragma once
#include "trigonometric.hpp"

#define PI glm::pi<float>()
#define rad(x) glm::radians<float>(x) // � -> radians
#define degrees(x) glm::degrees<float>(x) // radians -> �

// Window Dimensions
static const unsigned int windowWidth = 1280, windowHeight = 720;
static const unsigned int windowCenterX = windowWidth / 2, windowCenterY = windowHeight / 2;
