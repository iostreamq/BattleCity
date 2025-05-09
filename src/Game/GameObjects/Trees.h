#pragma once
#include "IGameObjects.h"
#include <memory>
#include <array>

namespace RenderEngine {
    class Sprite;
}

class Trees : public IGameObject {
public:

    enum EBlockLocation : uint8_t {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };
    Trees(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
     void Render() const override; 

private:
    void RenderBlock(const EBlockLocation& eBlockLocation) const;
    std::array<glm::vec2, 4> m_blockOffsets;
    std::shared_ptr<RenderEngine::Sprite> m_pSprite;
};
