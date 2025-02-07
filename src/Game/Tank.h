#pragma once
#include<memory>
#include<external/glm/vec2.hpp>

namespace Renderer {
	class AnimatedSprite;
}

class Tank {
public:

	enum class EOrientation {
		Top,
		Bottom,
		Left,
		Right
	};

	Tank(std::shared_ptr<Renderer::AnimatedSprite> pSprite, const float velocity, const glm::vec2& position);

	void Render() const;
	void setOrientation(const EOrientation orientation);
	void move(const bool move); //ее будем ставить тогда когда танк будет находиться в движении и когда он будет двигаться будет включаться анимация его спрайта  
	void update(const uint64_t delta);
    
private:
	EOrientation m_eOrientation;
	std::shared_ptr<Renderer::AnimatedSprite> m_pSprite;
	bool m_move;
	float m_velocity;
	glm::vec2 m_position;
	glm::vec2 m_moveOffset; // обозначает на какой оффсет перемещается танк если ориентация смотрит влево то и оффсет туда же смотрит
};