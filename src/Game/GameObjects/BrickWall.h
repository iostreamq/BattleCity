#pragma once
#include "IGameObjects.h"
#include <memory>
#include <array>
//#include <src/Physics/PhysicsEngine.h>

namespace RenderEngine {
    class Sprite;
}

class BrickWall : public IGameObject {
public:

    enum class EBrickWallType : uint8_t {
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

    enum class EBrickState : uint8_t {
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

    enum EBrickLocation : uint8_t {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };
     BrickWall(const EBrickWallType& eBrickWallType, const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
     void Render() const override; 
     void onCollisionStatic(const std::shared_ptr<IGameObject>& object,const uint8_t& location, const Physics::PhysicsEngine::EDirection& direction) override;
     
private:

    void getNewSubObject(const EBrickLocation& location,const Physics::PhysicsEngine::EDirection direction);
    void getNewAABB(const EBrickLocation& location);
    std::array<glm::vec2, 4> m_blockOffsets;
    void RenderBrick(const EBrickLocation& eBrickLocation) const;
    std::array<EBrickState, 4> m_eCurrentBrickState;
    std::array<std::shared_ptr<RenderEngine::Sprite>, 15> m_sprites;
};
