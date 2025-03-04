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

		struct FramesDescription {
			FramesDescription(const glm::vec2& _leftBottomUV, const glm::vec2& _rightTopUV, const uint64_t& _duration):
			leftBottomUV(_leftBottomUV),
			rightTopUV(_rightTopUV),
			duration(_duration)
			{}
			/// <summary>
			/// превет друг* (_)_|_(_)
			/// </summary>
			glm::vec2 leftBottomUV;
			glm::vec2 rightTopUV;
			uint64_t duration;

		};

		Sprite(std::shared_ptr<RenderEngine::Texture2D> pTexture,
			std::string&& initialSubTexture,	
		    std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram
		    );

		~Sprite();

		Sprite() = delete;
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete; // вопрос по &
		

		void Render(const glm::vec2& position 
					,const glm::vec2& size
					,const float rotation
				    ,const float layer = 0.f
					,const size_t frameId = 0) const;
		void insertFrames(std::vector<FramesDescription> framesDescriptions);
		uint64_t GetFrameDuration(const size_t frameId) const;
		size_t GetFramesCount();

	protected:
		 std::shared_ptr<RenderEngine::Texture2D> m_pTexture;
		 std::shared_ptr<RenderEngine::ShaderProgram> m_pShaderProgram;
		 VertexArray m_vertexArray;
		 VertexBuffer m_vertexsCoordsBuffer;
		 VertexBuffer m_textureCoordsBuffer;
		 indexBuffer  m_IndexBuffer;
		 std::vector<FramesDescription> m_framesDescription;
		 unsigned int lastFrame = 0;
	};

	
}