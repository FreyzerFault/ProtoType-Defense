#pragma once
#include "pch.h"

class DeltaTime
{
public:
	DeltaTime(const GLfloat deltaTime = 0.0f)
		: deltaTime(deltaTime)
	{
	}

	operator GLfloat() const { return deltaTime; }

	GLfloat getSeconds() const { return deltaTime; }
	GLfloat getMilliSeconds() const { return deltaTime * 1000.0f; }

private:
	GLfloat deltaTime;


};