#pragma once
#include "pch.h"

#define PI glm::pi<GLfloat>()
#define rad(x) glm::radians<GLfloat>(x) // º -> radians
#define degrees(x) glm::degrees<GLfloat>(x) // radians -> º

// Window Dimensions
static const GLuint windowWidth = 1280, windowHeight = 720;
static const GLuint windowCenterX = windowWidth / 2, windowCenterY = windowHeight / 2;
