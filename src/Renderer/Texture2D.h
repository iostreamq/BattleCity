#pragma once
#include "glad/glad.h"
#include <string>
#include "external/glm/vec2.hpp"
#include <map>

namespace RenderEngine {
	class Texture2D {
	public:

		struct subTexture2D {
			// нам нужно для тайтла коорды левого нижнего и правого угла тайтла
			glm::vec2 leftBottomUV; // лев нижний
			glm::vec2 rightTopUV; // правый  верх

			subTexture2D(const glm::vec2& _leftBottomUV, const glm::vec2& _rightTopUV) :
				leftBottomUV(_leftBottomUV),
				rightTopUV(_rightTopUV)
			{}
			//деф ктор берет фулл текстуру
			subTexture2D() :
				leftBottomUV(0.f),////////////////////
				rightTopUV(1.f) //////////////
			{}

		};

		Texture2D(const GLuint width, const GLuint height, const unsigned char* data, const unsigned channels = 4,
			const GLenum filter = GL_NEAREST, const GLenum wrapMode = GL_CLAMP_TO_EDGE);
			~Texture2D();
			Texture2D() = delete;
			Texture2D(const Texture2D&) = delete;
			Texture2D&operator=(const Texture2D&) = delete;
			Texture2D& operator=(Texture2D&& texture2D) noexcept;
			Texture2D(Texture2D&& texture2D) noexcept;

			void bind() const;
			void addSubTexture(std::string&& name, const glm::vec2& leftBottomUV, const glm::vec2& rightTopUV); // добавление сабтекс в сущ текс
			const subTexture2D& getSubTexture(const std::string& name) const; // получение сабтекс по имени
			unsigned int getWidth() const { return  m_width; }
			unsigned int getHeight() const { return m_height; }

	private:
		GLuint m_ID;
		GLenum m_mode;
		 unsigned int m_width;
		 unsigned int m_height;
		std::map<std::string, subTexture2D> m_subTextures;
	
	};
}