#include "Eagle.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"



Eagle::Eagle(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
	: IGameObject(EtypeOfObject::Eagle,position, size, rotation, layer)
	, m_pSpritesArray{
		ResourceManager::getSprite("eagle"),
		ResourceManager::getSprite("eagle_dead")
	}
	, m_eCurrentState(EEagleState::Alive)
{
	m_colliders.emplace_back(glm::vec2(0), m_size);
}


void Eagle::Render() const
{
	m_pSpritesArray[static_cast<uint8_t>(m_eCurrentState)]->Render(m_position, m_size, m_rotation, m_layer);
}

void Eagle::update(const double& delta)
{
	
}


