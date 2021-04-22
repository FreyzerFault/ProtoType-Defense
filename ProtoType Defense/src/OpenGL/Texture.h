#pragma once

#include <string>
#include <GL/glew.h>


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

private:
	uint32_t m_RendererID;
	std::string name;
};

