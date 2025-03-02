#include "Ice.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"



Ice::Ice(const glm::vec2& position, const glm::vec2& size, const float rotation)
    : IGameObject(position, size, rotation)
	, m_pSprite(ResourceManager::getSprite("ice"))
	, m_blockOffsets
	{
	glm::vec2(0, m_size.y / 2),
	glm::vec2(m_size.x / 2, m_size.y / 2),
	glm::vec2(0, 0),
	glm::vec2(m_size.x / 2, 0)
	}
{}

void Ice::RenderBlock(const EBlockLocation& eBlockLocation) const
{	
	m_pSprite->Render(m_position + m_blockOffsets[static_cast<size_t>(eBlockLocation)], m_size / 2.f, m_rotation);
}

void Ice::Render() const
{
		RenderBlock(EBlockLocation::TopLeft);
		RenderBlock(EBlockLocation::TopRight);
		RenderBlock(EBlockLocation::BottomLeft);
		RenderBlock(EBlockLocation::BottomRight);
}

