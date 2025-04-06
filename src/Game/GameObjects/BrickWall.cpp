#include "BrickWall.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

BrickWall::BrickWall(const EBrickWallType& eBrickWallType, const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
    : IGameObject(EtypeOfObject::BrickWall,position, size, rotation, layer)
    , m_eCurrentBrickState{EBrickState::Destroyed
                        ,  EBrickState::Destroyed
                        ,  EBrickState::Destroyed 
                        ,  EBrickState::Destroyed}
						, m_blockOffsets{
						  glm::vec2(0, m_size.y / 2),
						  glm::vec2(m_size.x / 2, m_size.y / 2),
						  glm::vec2(0, 0),
						  glm::vec2(m_size.x / 2, 0)
							}
{
	m_sprites[static_cast<size_t>(EBrickState::All)] = ResourceManager::getSprite("brickWall_All");
	m_sprites[static_cast<size_t>(EBrickState::TopLeft)] = ResourceManager::getSprite("brickWall_TopLeft");
	m_sprites[static_cast<size_t>(EBrickState::TopRight)] = ResourceManager::getSprite("brickWall_TopRight");
	m_sprites[static_cast<size_t>(EBrickState::Top)] = ResourceManager::getSprite("brickWall_Top");
	m_sprites[static_cast<size_t>(EBrickState::BottomLeft)] = ResourceManager::getSprite("brickWall_BottomLeft");
	m_sprites[static_cast<size_t>(EBrickState::Left)] = ResourceManager::getSprite("brickWall_Left");
	m_sprites[static_cast<size_t>(EBrickState::TopRight_BottomLeft)] = ResourceManager::getSprite("brickWall_TopRight_BottomLeft");
	m_sprites[static_cast<size_t>(EBrickState::Top_BottomLeft)] = ResourceManager::getSprite("brickWall_Top_BottomLeft");
	m_sprites[static_cast<size_t>(EBrickState::BottomRight)] = ResourceManager::getSprite("brickWall_BottomRight");
	m_sprites[static_cast<size_t>(EBrickState::TopLeft_BottomRight)] = ResourceManager::getSprite("brickWall_TopLeft_BottomRight");
	m_sprites[static_cast<size_t>(EBrickState::Right)] = ResourceManager::getSprite("brickWall_Right");
	m_sprites[static_cast<size_t>(EBrickState::Top_BottomRight)] = ResourceManager::getSprite("brickWall_Top_BottomRight");
	m_sprites[static_cast<size_t>(EBrickState::Bottom)] = ResourceManager::getSprite("brickWall_Bottom");
	m_sprites[static_cast<size_t>(EBrickState::TopLeft_Bottom)] = ResourceManager::getSprite("brickWall_TopLeft_Bottom");
	m_sprites[static_cast<size_t>(EBrickState::TopRight_Bottom)] = ResourceManager::getSprite("brickWall_TopRight_Bottom");


	switch (eBrickWallType)
	{
	case BrickWall::EBrickWallType::All:
		m_eCurrentBrickState.fill(EBrickState::All);
		m_colliders.emplace_back(glm::vec2(0.f, m_size.y / 2), glm::vec2(m_size.x / 2, m_size.y));
		m_colliders.emplace_back(glm::vec2(m_size / 2.f), glm::vec2(m_size));
		m_colliders.emplace_back(glm::vec2(0.f), glm::vec2(m_size / 2.f));
		m_colliders.emplace_back(glm::vec2(m_size.x / 2, 0.f), glm::vec2(m_size.x, m_size.y / 2));
		break;
	case BrickWall::EBrickWallType::Top:
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::TopLeft)] = EBrickState::All;
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::TopRight)] = EBrickState::All;	
		m_colliders.emplace_back(glm::vec2(0.f, m_size.y / 2), glm::vec2(m_size.x / 2, m_size.y));
		m_colliders.emplace_back(glm::vec2(m_size / 2.f), glm::vec2(m_size));
		m_colliders.emplace_back(glm::vec2(0.f));
		m_colliders.emplace_back(glm::vec2(0.f));
		break;
	case BrickWall::EBrickWallType::Bottom:
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomLeft)] = EBrickState::All;
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
		m_colliders.emplace_back(glm::vec2(0.f));
		m_colliders.emplace_back(glm::vec2(0.f));
		m_colliders.emplace_back(glm::vec2(0.f), glm::vec2(m_size / 2.f));
		m_colliders.emplace_back(glm::vec2(m_size.x / 2, 0.f), glm::vec2(m_size.x, m_size.y / 2));
		break;
	case BrickWall::EBrickWallType::Left:
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::TopLeft)] = EBrickState::All;
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomLeft)] = EBrickState::All;
		m_colliders.emplace_back(glm::vec2(0.f, m_size.y / 2), glm::vec2(m_size.x / 2, m_size.y));
		m_colliders.emplace_back(glm::vec2(0.f));
		m_colliders.emplace_back(glm::vec2(0.f), glm::vec2(m_size / 2.f));
		m_colliders.emplace_back(glm::vec2(0.f));
		break;
	case BrickWall::EBrickWallType::Right:
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::TopRight)] = EBrickState::All;
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
		m_colliders.emplace_back(glm::vec2(0.f));
		m_colliders.emplace_back(glm::vec2(m_size / 2.f), glm::vec2(m_size));
		m_colliders.emplace_back(glm::vec2(0.f));
		m_colliders.emplace_back(glm::vec2(m_size.x / 2, 0.f), glm::vec2(m_size.x, m_size.y / 2));
		break;
	case BrickWall::EBrickWallType::TopLeft:
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::TopLeft)] = EBrickState::All;
		break;
	case BrickWall::EBrickWallType::TopRight:
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::TopRight)] = EBrickState::All;
		break;
	case BrickWall::EBrickWallType::BottomLeft:
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomLeft)] = EBrickState::All;
		m_colliders.emplace_back(glm::vec2(0.f));
		m_colliders.emplace_back(glm::vec2(0.f));
		m_colliders.emplace_back(glm::vec2(0), glm::vec2(m_size.x / 2, m_size.y / 2));
		m_colliders.emplace_back(glm::vec2(0.f));		
		break;
	case BrickWall::EBrickWallType::BottomRight:
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
		m_colliders.emplace_back(glm::vec2(0.f));
		m_colliders.emplace_back(glm::vec2(0.f));
		m_colliders.emplace_back(glm::vec2(0.f));
		m_colliders.emplace_back(glm::vec2(m_size.x/2, 0.f), glm::vec2(m_size.x, m_size.y / 2));
		break;
	}

	
}

void BrickWall::getNewSubObject(const EBrickLocation& location, const Physics::PhysicsEngine::EDirection direction)
{
	const EBrickState BrickState = m_eCurrentBrickState[static_cast<size_t>(location)];
	switch (BrickState)
	{
	case EBrickState::All:
		switch (direction)
		{
		case Physics::PhysicsEngine::EDirection::Top:
			m_eCurrentBrickState[static_cast<size_t>(location)] = EBrickState::Bottom;
			break;
		case Physics::PhysicsEngine::EDirection::Bottom:
			m_eCurrentBrickState[static_cast<size_t>(location)] = EBrickState::Top;
			break;
		case Physics::PhysicsEngine::EDirection::Left:
			m_eCurrentBrickState[static_cast<size_t>(location)] = EBrickState::Right;
			break;
		case Physics::PhysicsEngine::EDirection::Right:
			m_eCurrentBrickState[static_cast<size_t>(location)] = EBrickState::Left;
			break;
		}
		break;
	case EBrickState::Top:
		switch (direction)
		{
		case Physics::PhysicsEngine::EDirection::Top:
			m_eCurrentBrickState[static_cast<size_t>(location)] = EBrickState::Destroyed;
			break;
		case Physics::PhysicsEngine::EDirection::Bottom:
			m_eCurrentBrickState[static_cast<size_t>(location)] = EBrickState::Destroyed;
			break;
		case Physics::PhysicsEngine::EDirection::Left:
			m_eCurrentBrickState[static_cast<size_t>(location)] = EBrickState::TopRight;
			break;
		case Physics::PhysicsEngine::EDirection::Right:
			m_eCurrentBrickState[static_cast<size_t>(location)] = EBrickState::TopLeft;
			break;
		}
		break;
	case EBrickState::Left:
		switch (direction)
		{
		case Physics::PhysicsEngine::EDirection::Top:
			m_eCurrentBrickState[static_cast<size_t>(location)] = EBrickState::BottomLeft;
			break;
		case Physics::PhysicsEngine::EDirection::Bottom:
			m_eCurrentBrickState[static_cast<size_t>(location)] = EBrickState::TopLeft;
			break;
		case Physics::PhysicsEngine::EDirection::Left:
			m_eCurrentBrickState[static_cast<size_t>(location)] = EBrickState::Destroyed;
			break;
		case Physics::PhysicsEngine::EDirection::Right:
			m_eCurrentBrickState[static_cast<size_t>(location)] = EBrickState::Destroyed;
			break;
		}
		break;
	case EBrickState::Right:
		switch (direction)
		{
		case Physics::PhysicsEngine::EDirection::Top:
			m_eCurrentBrickState[static_cast<size_t>(location)] = EBrickState::BottomRight;
			break;
		case Physics::PhysicsEngine::EDirection::Bottom:
			m_eCurrentBrickState[static_cast<size_t>(location)] = EBrickState::TopRight;
			break;
		case Physics::PhysicsEngine::EDirection::Left:
			m_eCurrentBrickState[static_cast<size_t>(location)] = EBrickState::Destroyed;
			break;
		case Physics::PhysicsEngine::EDirection::Right:
			m_eCurrentBrickState[static_cast<size_t>(location)] = EBrickState::Destroyed;
			break;
		}
		break;
	case EBrickState::Bottom:
		switch (direction)
		{
		case Physics::PhysicsEngine::EDirection::Top:
			m_eCurrentBrickState[static_cast<size_t>(location)] = EBrickState::Destroyed;
			break;
		case Physics::PhysicsEngine::EDirection::Bottom:
			m_eCurrentBrickState[static_cast<size_t>(location)] = EBrickState::Destroyed;
			break;
		case Physics::PhysicsEngine::EDirection::Left:
			m_eCurrentBrickState[static_cast<size_t>(location)] = EBrickState::BottomRight;
			break;
		case Physics::PhysicsEngine::EDirection::Right:
			m_eCurrentBrickState[static_cast<size_t>(location)] = EBrickState::BottomLeft;
			break;
		}
		break;
	default:
		m_eCurrentBrickState[static_cast<size_t>(location)] = EBrickState::Destroyed;
		break;
	}
}

void BrickWall::getNewAABB(const EBrickLocation& location)
{
	EBrickState currentStateToChange = m_eCurrentBrickState[static_cast<EBrickLocation>(location)];
	std::vector<Physics::AABB> vecCorrectColliders;
	vecCorrectColliders.reserve(4);
	uint8_t necessaryIndexOfCollider = static_cast<EBrickLocation>(location);

	switch (currentStateToChange)
	{
	case BrickWall::EBrickState::TopLeft:
		for (size_t i = 0; i < m_colliders.size(); i++)
		{
			if (i == necessaryIndexOfCollider)
			{
				vecCorrectColliders.emplace_back(Physics::AABB(glm::vec2(0, m_size.y/4) + m_blockOffsets[necessaryIndexOfCollider], glm::vec2(m_size.x / 4, m_size.y / 2) + m_blockOffsets[necessaryIndexOfCollider]));
			}
			else
			vecCorrectColliders.emplace_back(m_colliders[i]);
		}
		break;
	case BrickWall::EBrickState::TopRight:
		for (size_t i = 0; i < m_colliders.size(); i++)
		{
			if (i == necessaryIndexOfCollider)
			{
				vecCorrectColliders.emplace_back(Physics::AABB(m_size/4.f + m_blockOffsets[necessaryIndexOfCollider], m_size/2.f + m_blockOffsets[necessaryIndexOfCollider]));
			}
			else
			vecCorrectColliders.emplace_back(m_colliders[i]);
		}
		break;
	case BrickWall::EBrickState::Top:
		for (size_t i = 0; i < m_colliders.size(); i++)
		{
			if (i == necessaryIndexOfCollider)
			{
				vecCorrectColliders.emplace_back(Physics::AABB(glm::vec2(0.f, m_size.y/4) + m_blockOffsets[necessaryIndexOfCollider], m_size/2.f + m_blockOffsets[necessaryIndexOfCollider]));
			}
			else
			vecCorrectColliders.emplace_back(m_colliders[i]);
		}
		break;
	case BrickWall::EBrickState::BottomLeft:
		for (size_t i = 0; i < m_colliders.size(); i++)
		{
			if (i == necessaryIndexOfCollider)
			{
				vecCorrectColliders.emplace_back(Physics::AABB(glm::vec2(0.f) + m_blockOffsets[necessaryIndexOfCollider], glm::vec2(m_size.x / 4, m_size.y/4) + m_blockOffsets[necessaryIndexOfCollider]));
			}
			else
			vecCorrectColliders.emplace_back(m_colliders[i]);
		}
		break;
	case BrickWall::EBrickState::BottomRight:
		for (size_t i = 0; i < m_colliders.size(); i++)
		{
			if (i == necessaryIndexOfCollider)
			{
				vecCorrectColliders.emplace_back(Physics::AABB(glm::vec2(m_size.x/4.f, 0.f) + m_blockOffsets[necessaryIndexOfCollider], glm::vec2(m_size.x / 2, m_size.y / 4) + m_blockOffsets[necessaryIndexOfCollider]));
			}
			else
				vecCorrectColliders.emplace_back(m_colliders[i]);
		}
		break;
	case BrickWall::EBrickState::Left:
		for (size_t i = 0; i < m_colliders.size(); i++)
		{
			if (i == necessaryIndexOfCollider)
			{
				vecCorrectColliders.emplace_back(Physics::AABB(glm::vec2(0.f) + m_blockOffsets[necessaryIndexOfCollider], glm::vec2(m_size.x / 4, m_size.y/2) + m_blockOffsets[necessaryIndexOfCollider]));
			}
			else
			vecCorrectColliders.emplace_back(m_colliders[i]);
		}
		break;
	case BrickWall::EBrickState::Right:
		for (size_t i = 0; i < m_colliders.size(); i++)
		{
			if (i == necessaryIndexOfCollider)
			{
				vecCorrectColliders.emplace_back(Physics::AABB(glm::vec2(m_size.x/4, 0.f) + m_blockOffsets[necessaryIndexOfCollider], glm::vec2(m_size.x/2, m_size.y/2) + +m_blockOffsets[necessaryIndexOfCollider]));
			}
			else
			vecCorrectColliders.emplace_back(m_colliders[i]);
		}
		break;
	case BrickWall::EBrickState::Bottom:
		for (size_t i = 0; i < m_colliders.size(); i++)
		{
			if (i == necessaryIndexOfCollider)
			{
				vecCorrectColliders.emplace_back(Physics::AABB(glm::vec2(0.f) + m_blockOffsets[necessaryIndexOfCollider], glm::vec2(m_size.x/2, m_size.y/4) + m_blockOffsets[necessaryIndexOfCollider]));
			}
			else
			vecCorrectColliders.emplace_back(m_colliders[i]);
		}
		break;
	case BrickWall::EBrickState::Destroyed:
		for (size_t i = 0; i < m_colliders.size(); i++)
		{
			if (i == necessaryIndexOfCollider)
			{
				vecCorrectColliders.emplace_back(Physics::AABB(glm::vec2(0.f) + +m_blockOffsets[necessaryIndexOfCollider]));
			}
			else
			vecCorrectColliders.emplace_back(m_colliders[i]);
		}
		break;
	default:
		break;
	}
	m_colliders = vecCorrectColliders;
}

void BrickWall::RenderBrick(const EBrickLocation& eBrickLocation) const
{
	const EBrickState BrickState = m_eCurrentBrickState[static_cast<size_t>(eBrickLocation)];
	m_sprites[static_cast<size_t>(BrickState)]->Render(m_position + m_blockOffsets[static_cast<size_t>(eBrickLocation)], m_size / 2.f, m_rotation, m_layer);
}

void BrickWall::Render() const
{
	
	if(m_eCurrentBrickState[EBrickLocation::TopLeft] != EBrickState::Destroyed)
	RenderBrick(EBrickLocation::TopLeft);
	
	if (m_eCurrentBrickState[EBrickLocation::TopRight] != EBrickState::Destroyed)
	RenderBrick(EBrickLocation::TopRight);

	if (m_eCurrentBrickState[EBrickLocation::BottomLeft] != EBrickState::Destroyed) 
	RenderBrick(EBrickLocation::BottomLeft);

	if (m_eCurrentBrickState[EBrickLocation::BottomRight] != EBrickState::Destroyed)
	RenderBrick(EBrickLocation::BottomRight);  
}

void BrickWall::onCollisionStatic(const std::shared_ptr<IGameObject>& object,const uint8_t& location, const Physics::PhysicsEngine::EDirection& direction)
{
	if (object->getObjectType() == EtypeOfObject::Bullet)
	{
		EBrickLocation _location = static_cast<EBrickLocation>(location);
		getNewSubObject(_location, direction);
		getNewAABB(_location);
	}
}

