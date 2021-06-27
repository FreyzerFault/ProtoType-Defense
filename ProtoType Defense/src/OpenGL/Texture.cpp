#include "pch.h"
#include "Texture.h"

#include "GLDebugging.h"

Texture::Texture()
	: Texture("res/textures/0.png")
{
}

Texture::Texture(const std::string& path)
	: m_RendererID(0), name(path.substr(path.find_last_of('/')+1, path.find('.') - path.find_last_of('/')-1))
{
	if (!glIsTexture(m_RendererID)) {
		SDL_Surface* imagen = nullptr;

		imagen = IMG_Load(path.c_str());

		if (!imagen)
		{
			/* Fallo de carga de la imagen */
			printf("Image Loading Error: %s\n", IMG_GetError());
			return;
		}
		
		printf("Loading Image %s: %dx%d %dbpp\n", path.c_str(),
			imagen->w, imagen->h, imagen->format->BitsPerPixel);

		width = imagen->w; height = imagen->h;
		
		// TEXTURE:
		GLCall(glGenTextures(1, &m_RendererID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, imagen->w, imagen->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagen->pixels));
		glGenerateMipmap(GL_TEXTURE_2D);

		SDL_FreeSurface(imagen);
	}
}

Texture::Texture(const Texture& orig)
	: m_RendererID(orig.m_RendererID)
{
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

Texture& Texture::operator=(const Texture& orig)
{
	if (this != &orig)
	{
		m_RendererID = orig.m_RendererID;
	}
	return *this;
}

void Texture::Bind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}
