#pragma once

class DeltaTime
{
private:
	float deltaTime;

public:
	DeltaTime(const float deltaTime = 0.0f)
		: deltaTime(deltaTime)
	{
	}

	operator float() const { return deltaTime; }

	float getSeconds() const { return deltaTime; }
	float getMilliSeconds() const { return deltaTime * 1000.0f; }
	
};