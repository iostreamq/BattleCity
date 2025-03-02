#pragma once
#include "IGameObjects.h"
#include "../../Renderer/SpriteAnimator.h"
#include <memory>
#include <array>

namespace RenderEngine {
    class Sprite;
}

class Water : public IGameObject {
public:

    enum EBlockLocation : uint8_t {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };
    Water(const glm::vec2& position, const glm::vec2& size, const float rotation);
     void Render() const override;  
     void update(const uint64_t& delta) override;
    

private:
    void RenderBlock(const EBlockLocation& eBlockLocation) const;
    std::array<glm::vec2, 4> m_blockOffsets;
    std::shared_ptr<RenderEngine::Sprite> m_pSprite;
    RenderEngine::SpriteAnimator m_spriteAnimator;
};
