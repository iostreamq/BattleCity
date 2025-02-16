#include "Texture2D.h"


RenderEngine::Texture2D::Texture2D(const GLuint width, 
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

RenderEngine::Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_ID);
}


RenderEngine::Texture2D& RenderEngine::Texture2D::operator=(Texture2D&& texture2D) noexcept
{
	glDeleteTextures(1,&m_ID);
	m_ID = texture2D.m_ID;
	m_mode = texture2D.m_mode;
	m_width = texture2D.m_width;
	m_height = texture2D.m_height;
	texture2D.m_ID = 0;
	return *this;
}

RenderEngine::Texture2D::Texture2D(Texture2D&& texture2D) noexcept
{
	m_ID = texture2D.m_ID;
	m_mode = texture2D.m_mode;
	m_width = texture2D.m_width;
	m_height = texture2D.m_height;
	texture2D.m_ID = 0;
}

void RenderEngine::Texture2D::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void RenderEngine::Texture2D::addSubTexture(std::string&& name, const glm::vec2& leftBottomUV, const glm::vec2& rightTopUV)
{
	m_subTextures.emplace(std::move(name), subTexture2D(leftBottomUV, rightTopUV)); 
}

const RenderEngine::Texture2D::subTexture2D& RenderEngine::Texture2D::getSubTexture(const std::string& name) const
{
	
    auto it = m_subTextures.find(name);
	if (it != m_subTextures.end()) {
		return it->second;
	}
     
	const static subTexture2D defaultSubTexture; /// static здесь используется для того, чтобы объект defaultSubTexture был создан только один раз,
	//не занимал лишнюю память при каждом вызове функции, и оставался постоянным и доступным для всех вызовов этой функции.
	return defaultSubTexture;
}

