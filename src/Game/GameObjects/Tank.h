#pragma once
#include "external/glm/vec2.hpp"
#include <memory>
#include "IGameObjects.h"
#include "../../Renderer/SpriteAnimator.h"
#include "../../System/Timer.h"
#include "Bullet.h"

namespace RenderEngine {
    class Sprite;
}

    class Tank : public IGameObject {
    public:

        enum class EOrientation : uint8_t {
            Top,
            Bottom,
            Left,
            Right
        };

        Tank(const double maxVelocity,
            const glm::vec2& position,
            const glm::vec2& size,
            const float layer);

        void Render() const override;
        void setOrientation(const EOrientation eOrientation);
        void update(const double& delta) override;
        double GetMaxVelocity() const { return m_maxVelocity;}
        glm::vec2& GetPosStartScreen() { return m_positionStartScreen; }
        bool& GetStartScreen() { return is_StartScreenRunning; }
        void setVelocity(const double& velocity)  override;
        void fire();
        const unsigned int& getCurrentChoice() const { return m_currentChoice; }

    private:
        EOrientation m_eOrientation;
        EOrientation m_LastEOrientation;
        std::shared_ptr<RenderEngine::Sprite> m_pSprite_top;
        std::shared_ptr<RenderEngine::Sprite> m_pSprite_bottom;
        std::shared_ptr<RenderEngine::Sprite> m_pSprite_left;
        std::shared_ptr<RenderEngine::Sprite> m_pSprite_right;
        std::shared_ptr<Bullet> m_bullet;
        RenderEngine::SpriteAnimator m_spriteAnimator_top;
        RenderEngine::SpriteAnimator m_spriteAnimator_bottom;
        RenderEngine::SpriteAnimator m_spriteAnimator_left;
        RenderEngine::SpriteAnimator m_spriteAnimator_right;

        std::shared_ptr<RenderEngine::Sprite> m_pSprite_respawn;
        RenderEngine::SpriteAnimator m_spriteAnimator_respawn;

        std::shared_ptr<RenderEngine::Sprite> m_pSprite_shield;
        RenderEngine::SpriteAnimator m_spriteAnimator_shield;

        glm::vec2 m_positionStartScreen;

        Timer m_spawnTimer;
        Timer m_shieldTimer;

        double m_maxVelocity;
        bool m_isSpawning;
        bool m_hasShield;
        bool is_StartScreenRunning;
        unsigned int m_currentChoice;
    };
