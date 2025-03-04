#pragma once
#include "IGameObjects.h"
#include <memory>
#include <array>

namespace RenderEngine {
    class Sprite;
}

class Border : public IGameObject {
public:
    Border(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
     void Render() const override; 

private:
    std::shared_ptr<RenderEngine::Sprite> m_pSprite;
};
