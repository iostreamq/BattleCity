#pragma once
#include "IGameObjects.h"
#include "../../System/Timer.h"
#include <memory>
#include <array>

namespace RenderEngine {
    class Sprite;
}

class Bullet : public IGameObject {
public:
   
    Bullet(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
    void Render() const override;
    void update(const double& delta) override;
    bool& isActivity() { return m_isActivityBullet; };
    void onCollision() override;
    bool IsTimerLeft();
    bool checkColiders(EtypeOfObject typeOfObjectToCheck) override;
    void setDelay(const double& duration);
private:
    Timer m_bulletTimer;
    bool m_isActivityBullet;
    std::shared_ptr<RenderEngine::Sprite> m_pSprite;
};
