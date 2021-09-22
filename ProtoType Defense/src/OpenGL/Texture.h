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

	GLfloat getWidth() const { return width; }
	GLfloat getHeight() const { return height; }

private:
	GLuint m_RendererID;
	std::string name;

	GLfloat width;
	GLfloat height;
};

