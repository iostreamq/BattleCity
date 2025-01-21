#include "Texture2D.h"

Renderer::Texture2D::Texture2D(const GLuint width, 
	const GLuint height, 
	const unsigned char* data, 
	const unsigned channels, 
	const GLenum filter,
	const GLenum wrapMode): //GL_CLAMP_TO_EDGE чтобы видеть графические артефакты которые появляются из-за неправильного указания кординат текстур 
       m_width(width), m_height(height)
{
	switch (channels)
	{
	case 4:
		m_mode = GL_RGBA;
		break;
	case 3:
		m_mode = GL_RGB;
		break;
	default:
		m_mode = GL_RGBA;
	break;
	}

	glGenTextures(1, &m_ID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,m_ID); // биндим текстуру GL_TEXTURE_2D слот
	glTexImage2D(GL_TEXTURE_2D, 0, m_mode, m_width, m_height, 0, m_mode, GL_UNSIGNED_BYTE, data);// загружаем данные в память видеокарты// 3-сколько каналов будем использовать почему именно 2 раза ргб 
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);// по x просто будет пиксель растягиваться до конца
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);// по y просто будет пиксель растягиваться до конца
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Renderer::Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_ID);
}


Renderer::Texture2D& Renderer::Texture2D::operator=(Texture2D&& texture2D) noexcept
{
	glDeleteTextures(1,&m_ID);
	m_ID = texture2D.m_ID;
	m_mode = texture2D.m_mode;
	m_width = texture2D.m_width;
	m_height = texture2D.m_height;
	texture2D.m_ID = 0;
	return *this;
}

Renderer::Texture2D::Texture2D(Texture2D&& texture2D) noexcept
{
	m_ID = texture2D.m_ID;
	m_mode = texture2D.m_mode;
	m_width = texture2D.m_width;
	m_height = texture2D.m_height;
	texture2D.m_ID = 0;
}

void Renderer::Texture2D::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
}
