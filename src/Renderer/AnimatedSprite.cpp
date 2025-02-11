#include "AnimatedSprite.h"
#include <iostream>


namespace Renderer {
	AnimatedSprite::AnimatedSprite(std::shared_ptr<Renderer::Texture2D> pTexture,
		std::string&& initialSubTexture,
		std::shared_ptr<Renderer::ShaderProgram> pShaderProgram,
		const glm::vec2& position,
		const glm::vec2& size,
		const float rotation) :

		Sprite(std::move(pTexture), std::move(initialSubTexture), std::move(pShaderProgram), position, size, rotation) //??????????????????
	{
		m_pCurrentAnimationsDurations = m_statesMap.end();
	}

	void AnimatedSprite::insertState(std::string&& state, std::vector<std::pair<std::string, uint64_t>> subTexturesDuration)
	{
		m_statesMap.emplace(std::move(state), std::move(subTexturesDuration));
	}


	void AnimatedSprite::setState(std::string&& newState)
	{
		auto it = m_statesMap.find(std::move(newState)); //////////////////////////////////////////////////////////
		if (it == m_statesMap.end()) {
			std::cerr << "Can`t find THIS animation state" << newState << std::endl;
			return;
        }

		if (m_pCurrentAnimationsDurations != it) {

			m_currentAnimationTime = 0;
			m_currentFrame = 0;
			m_pCurrentAnimationsDurations = it;
			m_dirty = true;
		}
	}

	void AnimatedSprite::update(const uint64_t delta)  
	{
		if (m_pCurrentAnimationsDurations != m_statesMap.end()) {

			m_currentAnimationTime += delta;
			
			while (m_currentAnimationTime >= m_pCurrentAnimationsDurations->second[m_currentFrame].second) 
			{
				m_currentAnimationTime -= m_pCurrentAnimationsDurations->second[m_currentFrame].second;
				m_currentFrame++;
				m_dirty = true;
		        
				if (m_currentFrame == m_pCurrentAnimationsDurations->second.size()) {

					m_currentFrame = 0;
				}
			}
		
		}
	}

	void AnimatedSprite::Render() const
	{
		if (m_dirty) {
			auto subTexture = m_pTexture->getSubTexture(m_pCurrentAnimationsDurations->second[m_currentFrame].first);

			const GLfloat textureCoords[] = {
		  subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
		  subTexture.leftBottomUV.x,  subTexture.rightTopUV.y,
		  subTexture.rightTopUV.x, subTexture.rightTopUV.y,
		  subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
			}; // чтоб не мучаться делай 2 буфера. если бы мы не меняли корды текстур то все было бы в одном буфере(sprite.cpp)

			m_textureCoordsBuffer.update(&textureCoords, 2 * 4 * sizeof(GLfloat)); // передает определенные данные которые обновляют тек буфер
			m_dirty = false;
		}
		Sprite::Render();
	}


}