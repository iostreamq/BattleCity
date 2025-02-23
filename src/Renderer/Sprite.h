#pragma once
#include "glad/glad.h"
#include <memory>
#include "Texture2D.h"
#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "indexBuffer.h"
#include "VertexArray.h"
#include "external/glm/vec2.hpp"
#include "../Game/GameObjects/IGameObjects.h"

namespace RenderEngine {

	class Sprite
	{
	public:
		Sprite(std::shared_ptr<RenderEngine::Texture2D> pTexture,
			std::string&& initialSubTexture,	
		    std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram
		    );

		~Sprite();

		Sprite() = delete;
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete; // вопрос по &
		

		virtual void Render(const glm::vec2& position, const glm::vec2& size, const float rotation) const;
	

	protected:
		 std::shared_ptr<RenderEngine::Texture2D> m_pTexture;
		 std::shared_ptr<RenderEngine::ShaderProgram> m_pShaderProgram;
		 VertexArray m_vertexArray;
		 VertexBuffer m_vertexsCoordsBuffer;
		 VertexBuffer m_textureCoordsBuffer;
		 indexBuffer  m_IndexBuffer;
		
	};

	
}