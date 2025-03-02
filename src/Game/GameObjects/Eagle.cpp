#include "Eagle.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"



Eagle::Eagle(const glm::vec2& position, const glm::vec2& size, const float rotation)
	: IGameObject(position, size, rotation)
	, m_pSpritesArray{
		ResourceManager::getSprite("eagle"),
		ResourceManager::getSprite("eagle_dead")
	}
	, m_eCurrentState(EEagleState::Dead)
{}


void Eagle::Render() const
{
	m_pSpritesArray[static_cast<uint8_t>(m_eCurrentState)]->Render(m_position, m_size, m_rotation);
}

void Eagle::update(const uint64_t& delta)
{
	
}


