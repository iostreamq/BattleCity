#include "VertexArray.h"

Renderer::VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_id);
}

Renderer::VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_id);
}

Renderer::VertexArray& Renderer::VertexArray::operator=(VertexArray&& VertexArray) noexcept
{
	m_id = VertexArray.m_id;
	VertexArray.m_id = 0;
	return *this;
}

Renderer::VertexArray::VertexArray(VertexArray&& VertexArray) noexcept 
{
	m_id = VertexArray.m_id;
	VertexArray.m_id = 0;
}

void Renderer::VertexArray::addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout)
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


void Renderer::VertexArray::bind() const
{
	glBindVertexArray(m_id);

}

void Renderer::VertexArray::unbind() const
{
	glBindVertexArray(0);

}


