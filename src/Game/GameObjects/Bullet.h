#pragma once
#include "../../Resources/ResourceManager.h"
#include "../../System/Timer.h"
#include "../../Renderer/SpriteAnimator.h"
#include <memory>
#include <array>

class Bullet : public IGameObject {
public:
   
    Bullet(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
    void Render() const override;
    void update(const double& delta) override;
    bool& isActivity() { return m_isActivityBullet; };
    void onCollisionDynamic() override;
    bool IsTimerLeft();
    bool getActivityOfExplosion() { return m_isActivityExplosion; };
    bool checkColiders(EtypeOfObject typeOfObjectToCheck) override;
    void setDelay(const double& duration);
   
private:
    std::shared_ptr<RenderEngine::Sprite> m_pSprite_explosion;
    RenderEngine::SpriteAnimator m_SpriteAnimator_explosion;
    Timer m_bulletTimer;
    Timer m_explosionTimer;
    bool m_isActivityBullet;
    bool m_isActivityExplosion;
    std::shared_ptr<RenderEngine::Sprite> m_pSprite;
};
