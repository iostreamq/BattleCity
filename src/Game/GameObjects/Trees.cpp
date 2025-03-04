#include "Trees.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"



Trees::Trees(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
    : IGameObject(position, size, rotation,layer)
	, m_pSprite(ResourceManager::getSprite("trees"))
	, m_blockOffsets
	{
	glm::vec2(0, m_size.y / 2),
	glm::vec2(m_size.x / 2, m_size.y / 2),
	glm::vec2(0, 0),
	glm::vec2(m_size.x / 2, 0)
	}
{}

void Trees::RenderBlock(const EBlockLocation& eBlockLocation) const
{	
	m_pSprite->Render(m_position + m_blockOffsets[static_cast<size_t>(eBlockLocation)], m_size / 2.f, m_rotation, m_layer);
}

void Trees::Render() const
{
		RenderBlock(EBlockLocation::TopLeft);
		RenderBlock(EBlockLocation::TopRight);
		RenderBlock(EBlockLocation::BottomLeft);
		RenderBlock(EBlockLocation::BottomRight);
}

