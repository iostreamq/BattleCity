#include "BetonWall.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"
#include "BetonWall.h"


BetonWall::BetonWall(const EBetonWallType& eBetonWallType, const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
    : IGameObject(EtypeOfObject::BetonWall,position, size, rotation, layer)
    , m_eCurrentBlockState{ EBlockState::Destroyed
                        ,  EBlockState::Destroyed
                        ,  EBlockState::Destroyed
                        ,  EBlockState::Destroyed}
						, m_pSprite(ResourceManager::getSprite("betonWall"))
						, m_blockOffsets{
						  glm::vec2(0, m_size.y / 2),
						  glm::vec2(m_size.x / 2, m_size.y / 2),
						  glm::vec2(0, 0),
						  glm::vec2(m_size.x / 2, 0)
						}
{
	
    switch (eBetonWallType)
    {
    case EBetonWallType::All:
        m_eCurrentBlockState.fill(EBlockState::Enabled);
        m_colliders.emplace_back(glm::vec2(0), m_size);
        break;
    case EBetonWallType::Top:
        m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::TopLeft)] = EBlockState::Enabled;
        m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::TopRight)] = EBlockState::Enabled;
        m_colliders.emplace_back(glm::vec2(0, m_size.y / 2), m_size);
        break;
    case EBetonWallType::Bottom:
        m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::BottomLeft)] = EBlockState::Enabled;
        m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::BottomRight)] = EBlockState::Enabled;
        m_colliders.emplace_back(glm::vec2(0), glm::vec2(m_size.x, m_size.y / 2));
        break;
    case EBetonWallType::Left:
        m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::TopLeft)] = EBlockState::Enabled;
        m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::BottomLeft)] = EBlockState::Enabled;
        m_colliders.emplace_back(glm::vec2(0), glm::vec2(m_size.x / 2, m_size.y));
        break;
    case EBetonWallType::Right:
        m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::TopRight)] = EBlockState::Enabled;
        m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::BottomRight)] = EBlockState::Enabled;
        m_colliders.emplace_back(glm::vec2(m_size.x / 2, 0), m_size);
        break;
    case EBetonWallType::TopLeft:
        m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::TopLeft)] = EBlockState::Enabled;
        m_colliders.emplace_back(glm::vec2(0, m_size.y / 2), glm::vec2(m_size.x / 2, m_size.y));
        break;
    case EBetonWallType::TopRight:
        m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::TopRight)] = EBlockState::Enabled;
        m_colliders.emplace_back(glm::vec2(m_size.x / 2, m_size.y / 2), m_size);
        break;
    case EBetonWallType::BottomLeft:
        m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::BottomLeft)] = EBlockState::Enabled;
        m_colliders.emplace_back(glm::vec2(0), glm::vec2(m_size.x / 2, m_size.y / 2));
        break;
    case EBetonWallType::BottomRight:
        m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::BottomRight)] = EBlockState::Enabled;
        m_colliders.emplace_back(glm::vec2(m_size.x / 2, 0), glm::vec2(m_size.x, m_size.y / 2));
        break;
    }
}

void BetonWall::RenderBlock(const EBlockLocation& eBlockLocation) const 
{	
	m_pSprite->Render(m_position + m_blockOffsets[static_cast<size_t>(eBlockLocation)], m_size / 2.f, m_rotation,m_layer);
}

void BetonWall::Render() const
{
	
	if(m_eCurrentBlockState[EBlockLocation::TopLeft] != EBlockState::Destroyed)
		RenderBlock(EBlockLocation::TopLeft);
	
	if (m_eCurrentBlockState[EBlockLocation::TopRight] != EBlockState::Destroyed)
		RenderBlock(EBlockLocation::TopRight);

	if (m_eCurrentBlockState[EBlockLocation::BottomLeft] != EBlockState::Destroyed)
		RenderBlock(EBlockLocation::BottomLeft);

	if (m_eCurrentBlockState[EBlockLocation::BottomRight] != EBlockState::Destroyed)
		RenderBlock(EBlockLocation::BottomRight);
}

void BetonWall::update(const double& delta)
{
}
