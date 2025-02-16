#pragma once
#include "glad/glad.h"

namespace RenderEngine {
	class indexBuffer {
	public:
		indexBuffer() {}
		~indexBuffer();

		indexBuffer(const indexBuffer&) = delete;
		indexBuffer& operator=(const indexBuffer&) = delete;
		indexBuffer& operator=(indexBuffer&& indexBuffer) noexcept;
		indexBuffer(indexBuffer&& indexBuffer) noexcept;

		void init(const void* data, const unsigned int count); // point na dannie and size of dannie 
		void bind() const;
		void unbind() const;
		unsigned int getCount() const { return m_count; } 

	private:
		GLuint m_id = 0;
		unsigned int m_count = 0;
	};
}