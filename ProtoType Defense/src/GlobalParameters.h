#pragma once
#include "trigonometric.hpp" // rad() & degrees()
#include <ext/scalar_constants.hpp> // PI()
#include <ext/matrix_clip_space.hpp>
#include <ext/matrix_transform.hpp>

#define PI glm::pi<float>()
#define rad(x) glm::radians<float>(x) // � -> radians
#define degrees(x) glm::degrees<float>(x) // radians -> �

// Window Dimensions
static const uint32_t windowWidth = 1280, windowHeight = 720;
static const uint32_t windowCenterX = windowWidth / 2, windowCenterY = windowHeight / 2;
