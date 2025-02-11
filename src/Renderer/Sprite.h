#pragma once
#include "glad/glad.h"
#include <memory>
#include "Texture2D.h"
#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "indexBuffer.h"
#include "VertexArray.h"
#include "external/glm/vec2.hpp"

namespace Renderer {

	class Sprite
	{
	public:
		Sprite(std::shared_ptr<Renderer::Texture2D> pTexture,
			std::string&& initialSubTexture,	
		    std::shared_ptr<Renderer::ShaderProgram> pShaderProgram, 
		    const glm::vec2& position = glm::vec2(0.f), 
			const glm::vec2& size = glm::vec2(1.f), 
			const float rotation = 0.f);

		~Sprite();

		Sprite() = delete;
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete; // вопрос по &

		virtual void Render() const;
		void setPosition(const glm::vec2& position);
		void setSize(const glm::vec2& size);
		void setRotation(const float rotation);

	protected:
		 std::shared_ptr<Renderer::Texture2D> m_pTexture;
		 std::shared_ptr<Renderer::ShaderProgram> m_pShaderProgram;
		 glm::vec2 m_position;
		 glm::vec2 m_size;
		 float m_rotation;
		 VertexArray m_vertexArray;
		 VertexBuffer m_vertexsCoordsBuffer;
		 VertexBuffer m_textureCoordsBuffer;
		 indexBuffer  m_IndexBuffer;
	};

	
}