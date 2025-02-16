#include "VertexArray.h"

RenderEngine::VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_id);
}

RenderEngine::VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_id);
}

RenderEngine::VertexArray& RenderEngine::VertexArray::operator=(VertexArray&& VertexArray) noexcept
{
	m_id = VertexArray.m_id;
	VertexArray.m_id = 0;
	return *this;
}

RenderEngine::VertexArray::VertexArray(VertexArray&& VertexArray) noexcept 
{
	m_id = VertexArray.m_id;
	VertexArray.m_id = 0;
}

void RenderEngine::VertexArray::addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout)
{
	bind();
	vertexBuffer.bind();
	const auto& layoutElements = layout.getLayoutElements();
	GLbyte* offset = nullptr;
	for (unsigned int i = 0; i < layoutElements.size(); i++) {

		const auto& currentLayoutElement = layoutElements[i];
		GLuint currentAttribIndex = m_buffersCount + i;
		glEnableVertexAttribArray(currentAttribIndex);
		glVertexAttribPointer(currentAttribIndex, currentLayoutElement.count, currentLayoutElement.type, currentLayoutElement.normalized, layout.getStride(), offset);
		offset += currentLayoutElement.size;
	}
	m_buffersCount += layoutElements.size();
}


void RenderEngine::VertexArray::bind() const
{
	glBindVertexArray(m_id);

}

void RenderEngine::VertexArray::unbind() const
{
	glBindVertexArray(0);

}


