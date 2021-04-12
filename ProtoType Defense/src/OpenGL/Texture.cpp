#include "Texture.h"
#include "GLDebugging.h"
#include "SDL_image.h"

Texture::Texture()
	: Texture(getFolderPath() + "DOGO.png")
{
}

Texture::Texture(const std::string& path)
	: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	if (!glIsTexture(m_RendererID)) {
		SDL_Surface* imagen = NULL;

		imagen = IMG_Load(path.c_str());

		if (!imagen)
		{
			/* Fallo de carga de la imagen */
			printf("Image Loading Error: %s\n", IMG_GetError());
			return;
		}
		m_LocalBuffer = (unsigned char*) imagen->pixels;
		
		printf("Loading Image %s: %dx%d %dbpp\n", path.c_str(),
			imagen->w, imagen->h, imagen->format->BitsPerPixel);

		m_Width = imagen->w;
		m_Height = imagen->h;
		m_BPP = imagen->format->BitsPerPixel;

		// TEXTURE:
		GLCall(glGenTextures(1, &m_RendererID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));

		GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		SDL_FreeSurface(imagen);
	}
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
		m_Width = orig.m_Width;
		m_Height = orig.m_Height;
		m_FilePath = orig.m_FilePath;
		m_BPP = orig.m_BPP;
		m_LocalBuffer = orig.m_LocalBuffer;
	}
	return *this;
}

void Texture::Bind(unsigned int slot /*= 0*/) const
{
	ASSERT(slot <= MAX_TEXTURE_SLOTS);

	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
