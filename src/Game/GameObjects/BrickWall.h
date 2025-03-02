#pragma once
#include "IGameObjects.h"
#include <memory>
#include <array>

namespace RenderEngine {
    class Sprite;
}

class BrickWall : public IGameObject {
public:

    enum class EBrickWallType {
        All,
        Top,
        Bottom,
        Left,
        Right,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    enum class EBrickState {
        All,
		TopLeft,
		TopRight,
		Top,
		BottomLeft,
		Left,
		TopRight_BottomLeft,
		Top_BottomLeft,
		BottomRight,
		TopLeft_BottomRight,
		Right,
		Top_BottomRight,
		Bottom,
		TopLeft_Bottom,
		TopRight_Bottom,
        Destroyed
    };

    enum EBrickLocation {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };
    BrickWall(const EBrickWallType& eBrickWallType, const glm::vec2& position, const glm::vec2& size, const float rotation);
     void Render() const override; // убрал виртуал........................................................
     void update(const uint64_t delta) override;

private:
    std::array<glm::vec2, 4> m_blockOffsets;
    void RenderBrick(const EBrickLocation& eBrickLocation) const;
    std::array<EBrickState, 4> m_eCurrentBrickState;
    std::array<std::shared_ptr<RenderEngine::Sprite>, 15> m_sprites;
};
