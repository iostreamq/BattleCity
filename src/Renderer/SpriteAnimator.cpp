#include "SpriteAnimator.h"
#include "Sprite.h"


RenderEngine::SpriteAnimator::SpriteAnimator(std::shared_ptr<Sprite> pSprite)
	: 
	  m_pSprite(std::move(pSprite)),
	  m_currentFrame(0),
	  m_currentFrameDuration(m_pSprite->GetFrameDuration(m_currentFrame)),
      m_currentAnimationTime(0), 
	  m_totalDuration(m_pSprite->GetTotalDuration())
{}

void RenderEngine::SpriteAnimator::reset()
{
	m_currentFrameDuration = 0;		
	m_currentAnimationTime = 0;
	m_currentFrame = 0;
}

void RenderEngine::SpriteAnimator::update(const double& delta)
{
	{
			m_currentAnimationTime += delta;

			while (m_currentAnimationTime >= m_currentFrameDuration)
			{
				m_currentAnimationTime -= m_currentFrameDuration;
				m_currentFrame++;

				if (m_currentFrame == m_pSprite->GetFramesCount())
				{
					m_currentFrame = 0;
				}
				m_currentFrameDuration = m_pSprite->GetFrameDuration(m_currentFrame);
			}

		
	}
}
