#include "indexBuffer.h"

RenderEngine::indexBuffer::~indexBuffer()
{
	glDeleteBuffers(1, &m_id);
}

RenderEngine::indexBuffer& RenderEngine::indexBuffer::operator=(indexBuffer&& indexBuffer) noexcept
{
	m_id = indexBuffer.m_id;
	indexBuffer.m_id = 0;
	return *this;
}

RenderEngine::indexBuffer::indexBuffer(indexBuffer&& indexBuffer) noexcept
{
	m_id = indexBuffer.m_id;
	indexBuffer.m_id = 0;
}


void RenderEngine::indexBuffer::init(const void* data, const unsigned int count)
{
	m_count = count;
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(GLuint), data, GL_STATIC_DRAW);

}

void RenderEngine::indexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);

}

void RenderEngine::indexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
