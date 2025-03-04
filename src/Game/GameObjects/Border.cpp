#include "Border.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"



Border::Border(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
    : IGameObject(position, size, rotation,layer)
	, m_pSprite(ResourceManager::getSprite("border"))

{}


void Border::Render() const
{
	m_pSprite->Render(m_position, m_size, m_rotation, m_layer);
}

