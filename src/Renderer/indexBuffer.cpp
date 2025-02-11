#include "indexBuffer.h"

Renderer::indexBuffer::~indexBuffer()
{
	glDeleteBuffers(1, &m_id);
}

Renderer::indexBuffer& Renderer::indexBuffer::operator=(indexBuffer&& indexBuffer) noexcept
{
	m_id = indexBuffer.m_id;
	indexBuffer.m_id = 0;
	return *this;
}

Renderer::indexBuffer::indexBuffer(indexBuffer&& indexBuffer) noexcept
{
	m_id = indexBuffer.m_id;
	indexBuffer.m_id = 0;
}


void Renderer::indexBuffer::init(const void* data, const unsigned int size)
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size/*sizeof(data)*/, data, GL_STATIC_DRAW);

}

void Renderer::indexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);

}

void Renderer::indexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
