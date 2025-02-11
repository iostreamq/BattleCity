#pragma once
#include "glad/glad.h"

namespace Renderer {
	class indexBuffer {
	public:
		indexBuffer() {}
		~indexBuffer();

		indexBuffer(const indexBuffer&) = delete;
		indexBuffer& operator=(const indexBuffer&) = delete;
		indexBuffer& operator=(indexBuffer&& indexBuffer) noexcept;
		indexBuffer(indexBuffer&& indexBuffer) noexcept;

		void init(const void* data, const unsigned int size); // point na dannie and size of dannie 
		void bind() const;
		void unbind() const;

	private:
		GLuint m_id = 0;
	};
}