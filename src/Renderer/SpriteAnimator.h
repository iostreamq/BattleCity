#pragma once
#include<memory>


namespace RenderEngine {
	class Sprite;
	class SpriteAnimator
	{
	public:
		SpriteAnimator(std::shared_ptr<RenderEngine::Sprite> pSprite);
		size_t getCurrentFrame() const { return m_currentFrame; }
		void ResetFrame() { m_currentFrame = 0; }
		void update(const double& delta);

	private:
		std::shared_ptr<Sprite> m_pSprite;
		size_t m_currentFrame;
		double m_currentFrameDuration;
		double m_currentAnimationTime;
	};
}