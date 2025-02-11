#pragma once
#include<vector>
#include"glad/glad.h"

namespace Renderer {

	struct VertexBufferLayoutElement
	{
		GLint count;
		GLenum type;
		GLboolean normalized;
		unsigned long long size; // unsigned int
		/*VertexBufferLayoutElement(GLint c, GLenum t, GLboolean n, unsigned int s)
			: count(c), type(t), normalized(n), size(s) {}*/
	};
	class VertexBufferLayout
	{
	public:
		VertexBufferLayout() = default;
		~VertexBufferLayout() = default;
		
		void reserveElements(const size_t count); ///....................................
		unsigned int getStride() const { return m_stride; };
		void addElementLayoutFloat(const unsigned int count, const bool normalized);
		const std::vector<VertexBufferLayoutElement>& getLayoutElements() const { return m_layoutElements; } //..................................

	private:
		std::vector<VertexBufferLayoutElement> m_layoutElements;
		unsigned int m_stride = 0;
	};

}
 