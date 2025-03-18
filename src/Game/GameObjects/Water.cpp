#include "Water.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"



Water::Water(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
    : IGameObject(EtypeOfObject::Water,position, size, rotation,layer)
	, m_pSprite(ResourceManager::getSprite("water"))
	, m_spriteAnimator(m_pSprite)
	, m_blockOffsets
	{
	glm::vec2(0, m_size.y / 2),
	glm::vec2(m_size.x / 2, m_size.y / 2),
	glm::vec2(0, 0),
	glm::vec2(m_size.x / 2, 0)
	}
{
	m_colliders.emplace_back(glm::vec2(0), m_size);
}

void Water::RenderBlock(const EBlockLocation& eBlockLocation) const
{	
	m_pSprite->Render(m_position + m_blockOffsets[static_cast<size_t>(eBlockLocation)], m_size / 2.f, m_rotation, m_layer, m_spriteAnimator.getCurrentFrame());
}

void Water::Render() const
{
		RenderBlock(EBlockLocation::TopLeft);
		RenderBlock(EBlockLocation::TopRight);
		RenderBlock(EBlockLocation::BottomLeft);
		RenderBlock(EBlockLocation::BottomRight);
}

void Water::update(const double& delta)
{
	m_spriteAnimator.update(delta);
}

