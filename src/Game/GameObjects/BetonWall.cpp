#include "BetonWall.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"
#include "BetonWall.h"


BetonWall::BetonWall(const EBetonWallType& eBetonWallType, const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
    : IGameObject(position, size, rotation, layer)
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
	case BetonWall::EBetonWallType::All:
		m_eCurrentBlockState.fill(EBlockState::Enabled);
		break;
	case BetonWall::EBetonWallType::Top:
		m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::TopLeft)] = EBlockState::Enabled;
		m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::TopRight)] =EBlockState::Enabled;
		break;
	case BetonWall::EBetonWallType::Bottom:
		m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::BottomLeft)] =EBlockState::Enabled;
		m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::BottomRight)] =EBlockState::Enabled;
		break;
	case BetonWall::EBetonWallType::Left:
		m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::TopLeft)] =EBlockState::Enabled;
		m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::BottomLeft)] =EBlockState::Enabled;
		break;
	case BetonWall::EBetonWallType::Right:
		m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::TopRight)] =EBlockState::Enabled;
		m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::BottomRight)] =EBlockState::Enabled;
		break;
	case BetonWall::EBetonWallType::TopLeft:
		m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::TopLeft)] =EBlockState::Enabled;
		break;
	case BetonWall::EBetonWallType::TopRight:
		m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::TopRight)] =EBlockState::Enabled;
		break;
	case BetonWall::EBetonWallType::BottomLeft:
		m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::BottomLeft)] =EBlockState::Enabled;
		break;
	case BetonWall::EBetonWallType::BottomRight:
		m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::BottomRight)] =EBlockState::Enabled;
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
