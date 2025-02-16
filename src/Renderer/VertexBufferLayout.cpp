#include "VertexBufferLayout.h"


void RenderEngine::VertexBufferLayout::reserveElements(const size_t count)
{
	m_layoutElements.reserve(count); //......capacity
}

void RenderEngine::VertexBufferLayout::addElementLayoutFloat(const unsigned int count, const bool normalized)
{
	m_layoutElements.push_back(VertexBufferLayoutElement{static_cast<GLint>(count), GL_FLOAT, normalized, count * sizeof(GLfloat)});///////,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
	m_stride += m_layoutElements.back().size;///.............................
}
