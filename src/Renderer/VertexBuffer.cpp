#include "VertexBuffer.h"

RenderEngine::VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_id);
}

RenderEngine::VertexBuffer& RenderEngine::VertexBuffer::operator=(VertexBuffer&& vertexBuffer) noexcept
{
	m_id = vertexBuffer.m_id;
	vertexBuffer.m_id = 0;
	return *this;
}

RenderEngine::VertexBuffer::VertexBuffer(VertexBuffer&& vertexBuffer) noexcept 
{
	m_id = vertexBuffer.m_id;
	vertexBuffer.m_id = 0;
}


void RenderEngine::VertexBuffer::init(const void* data, const unsigned int size)
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); //&ptr даёт адрес переменной ptr (то есть место, где хранится сам указатель))))))))))))))))))

}

void RenderEngine::VertexBuffer::update(const void* data, const unsigned int size) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);

}

void RenderEngine::VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);

}

void RenderEngine::VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}
