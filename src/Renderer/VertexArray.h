#pragma once
#include "glad/glad.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace RenderEngine {
	class VertexArray {
	public:
		~VertexArray();
		VertexArray();
		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;
		VertexArray& operator=(VertexArray&& VertexArray) noexcept;
		VertexArray(VertexArray&& VertexArray) noexcept;

		void addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);
		void bind() const;
		void unbind() const;

	private:
		GLuint m_id = 0;
		size_t m_buffersCount = 0;

	};
}