#pragma once
#include "glad/glad.h"
#include <memory>
#include "Texture2D.h"
#include "ShaderProgram.h"
#include "external/glm/vec2.hpp"
#include "Sprite.h"
#include <map>
#include <vector>



namespace Renderer {

	class AnimatedSprite : public Sprite
	{
	public:
		AnimatedSprite(std::shared_ptr<Renderer::Texture2D> pTexture,
			std::string&& initialSubTexture,	
		    std::shared_ptr<Renderer::ShaderProgram> pShaderProgram, 
		    const glm::vec2& position = glm::vec2(0.f), 
			const glm::vec2& size = glm::vec2(1.f), 
			const float rotation = 0.f);

		void insertState(std::string&& state, std::vector<std::pair<std::string, uint64_t>> subTexturesDuration);

		void Render() const override;
		
		void setState(std::string&& newState);
		void update(const uint64_t delta); // время прошедшее с момента последнего кадра, то есть каждый кадр не моментально просчитывается, а какое-то время и длительность
	    // прошедшая с момента последнего кадра мы передаем сюда и относительно нее мы расчитываем когда наступит следующий кадр
	private:
		std::map <std::string, std::vector<std::pair<std::string, uint64_t>>> m_statesMap; //различные состояния спрайта и длительность кадра спрайта
	   // кокретное состояние будет иметь анимацию-последовательность кадров, то есть к каждому состоянию идет последовательность кадров и каждому кадру своя длительность
		std::map <std::string, std::vector<std::pair<std::string, uint64_t>>>::const_iterator m_pCurrentAnimationsDurations;
		size_t m_currentFrame = 0;
		uint64_t m_currentAnimationTime = 0; 
		mutable bool m_dirty = false; 
	 };

	
}