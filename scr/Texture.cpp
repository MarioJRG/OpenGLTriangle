#include "Texture.h"
#include "stb_image/stb_image.h"
Texture::Texture(const std::string& path) :
	m_FilePath(path), m_LocalBuffer(nullptr), m_heigh(0), m_width(0),m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_width, &m_heigh,&m_BPP, 4);
	glGenTextures(1, &m_RenderId);
	glBindTexture(GL_TEXTURE_2D, m_RenderId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_heigh, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_LocalBuffer) {
		stbi_image_free(m_LocalBuffer);
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_RenderId);
}

void Texture::Bind(const int slot) const
{
	glActiveTexture(GL_TEXTURE0+slot);
	glBindTexture(GL_TEXTURE_2D, m_RenderId);
}

void Texture::unBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
