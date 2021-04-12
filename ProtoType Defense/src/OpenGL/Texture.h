#pragma once

#include <string>

#define textureFolderPath Texture::getFolderPath()

class Texture
{
	static const unsigned int MAX_TEXTURE_SLOTS = 31;

private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

public:
	Texture();
	Texture(const std::string& path);
	~Texture();

	Texture& operator=(const Texture& orig);

	void Bind(unsigned int slot = 0) const; // MAX 31
	void Unbind() const;

	inline int getWidth() const { return m_Width; };
	inline int getHeight() const { return m_Height; };

	static std::string getFolderPath() { return "res/textures/";}

};

