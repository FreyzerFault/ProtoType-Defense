#pragma once
#include "pch.h"

#define PI glm::pi<float>()
#define rad(x) glm::radians<float>(x) // � -> radians
#define degrees(x) glm::degrees<float>(x) // radians -> �

// Window Dimensions
static const uint32_t windowWidth = 1280, windowHeight = 720;
static const uint32_t windowCenterX = windowWidth / 2, windowCenterY = windowHeight / 2;
