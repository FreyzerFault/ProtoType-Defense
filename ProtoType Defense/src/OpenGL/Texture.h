#pragma once
#include "pch.h"

class Texture
{
public:
	Texture();
	Texture(const std::string& path);
	Texture(const Texture& orig);
	~Texture();

	Texture& operator=(const Texture& orig);

	void Bind() const; // MAX 31

	const std::string& getName() const { return name; }

	float getWidth() const { return width; }
	float getHeight() const { return height; }

private:
	uint32_t m_RendererID;
	std::string name;

	float width;
	float height;
};

