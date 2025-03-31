#include "Tank.h"
#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"
#include <iostream>
Tank::Tank(const double maxVelocity,
    const glm::vec2& position,
    const glm::vec2& size,
    const float layer)
    : IGameObject(EtypeOfObject::Tank,position, size, 0.f, layer)
    , m_eOrientation(EOrientation::Top)
    , m_pSprite_top(ResourceManager::getSprite("tankSprite_top"))
    , m_pSprite_bottom(ResourceManager::getSprite("tankSprite_bottom"))
    , m_pSprite_left(ResourceManager::getSprite("tankSprite_left"))
    , m_pSprite_right(ResourceManager::getSprite("tankSprite_right"))
    , m_bullet(std::make_shared<Bullet>(m_position + m_size/4.f,m_size/2.f, 0.f,layer))
    , m_spriteAnimator_top(m_pSprite_top)
    , m_spriteAnimator_bottom(m_pSprite_bottom)
    , m_spriteAnimator_left(m_pSprite_left)
    , m_spriteAnimator_right(m_pSprite_right)
    , m_pSprite_respawn(ResourceManager::getSprite("respawn"))
    , m_pSprite_shield(ResourceManager::getSprite("shield"))
    , m_spriteAnimator_respawn(m_pSprite_respawn)
    , m_spriteAnimator_shield(m_pSprite_shield)
    , m_maxVelocity(maxVelocity)
    , m_isSpawning(true)
    , m_hasShield(false)

  
{
    m_spawnTimer.setCallback(
        [&]()
        {
            m_isSpawning = false;
            m_hasShield = true;
            m_shieldTimer.start(2000);
        }
                            );

    m_spawnTimer.start(1500);

    m_shieldTimer.setCallback(
            [&]()
            {
                m_hasShield = false;
            }
                             );
  
   
    m_colliders.emplace_back(glm::vec2(0.f), m_size);
    Physics::PhysicsEngine::addDynamicGameObject(m_bullet);
 
}       

void Tank::Render() const 
{
    
    if (m_isSpawning)
    {
        m_pSprite_respawn->Render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_respawn.getCurrentFrame());
    }

    else
    {
        switch (m_eOrientation)
        {
        case Tank::EOrientation::Top:
            m_pSprite_top->Render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_top.getCurrentFrame());
            break;
        case Tank::EOrientation::Bottom:
            m_pSprite_bottom->Render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_bottom.getCurrentFrame());
            break;
        case Tank::EOrientation::Left:
            m_pSprite_left->Render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_left.getCurrentFrame());
            break;
        case Tank::EOrientation::Right:
            m_pSprite_right->Render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_right.getCurrentFrame());
            break;
        }

        if (m_hasShield) 
        {
            m_pSprite_shield->Render(m_position, m_size, m_rotation, m_layer + 0.1f, m_spriteAnimator_shield.getCurrentFrame());
        }

        // все условия прописаны внутри, не оч логично но работает)))

        /*if (m_bullet->isActivity())
        {*/ 
           m_bullet->Render();
          
        /*}*/
    }
}

void Tank::fire()
{
    if (m_bullet->IsTimerLeft())
    {
        // Устанавливаем положение пули относительно танка только один раз
        m_bullet->getCurrentPosition() = m_position + m_size / 4.f + m_size * m_direction/4.f;
        // Устанавливаем направление и угол пули в зависимости от текущей ориентации танка
        switch (m_eOrientation)
        {
        case EOrientation::Top:
            m_bullet->getCurrentDirection() = { 0.f, 1.f };
            m_bullet->getCurrentRotation() = 0.f;
            break;
        case EOrientation::Bottom:
            m_bullet->getCurrentDirection() = { 0.f, -1.f };
            m_bullet->getCurrentRotation() = -180.f;
            break;
        case EOrientation::Left:
            m_bullet->getCurrentDirection() = { -1.f, 0.f };
            m_bullet->getCurrentRotation() = -270.f;
            break;
        case EOrientation::Right:
            m_bullet->getCurrentDirection() = { 1.f, 0.f };
            m_bullet->getCurrentRotation() = -90.f;
            break;
        }
        m_bullet->setVelocity(0.1f);
        m_bullet->setDelay(1500);
        
    }
}

void Tank::setOrientation(const EOrientation eOrientation)
{
    if (m_eOrientation == eOrientation)
    {
        return;
    }

    m_eOrientation = eOrientation;
    switch (m_eOrientation)
    {
    case Tank::EOrientation::Top:
        m_direction.x = 0.f;
        m_direction.y = 1.f;
        break;
    case Tank::EOrientation::Bottom:
        m_direction.x = 0.f;
        m_direction.y = -1.f;
        break;
    case Tank::EOrientation::Left:
        m_direction.x = -1.f;
        m_direction.y = 0.f;
        break;
    case Tank::EOrientation::Right:
        m_direction.x = 1.f;
        m_direction.y = 0.f;
        break;
    }
}

void Tank::update(const double& delta)
{
 

    if (m_isSpawning)
    {
        m_spawnTimer.update(delta);
        m_spriteAnimator_respawn.update(delta);
    }

    else 
    {
        if (m_hasShield)
        {
            m_shieldTimer.update(delta);
            m_spriteAnimator_shield.update(delta);
        }
        /*if (!m_bullet->IsTimerLeft())
        {*/
            m_bullet->update(delta);
        /*}*/

        if (m_velocity > 0)
        {
           
            switch (m_eOrientation)
            {
            case Tank::EOrientation::Top:
                if (m_eOrientation == m_LastEOrientation)
                    m_spriteAnimator_top.update(delta);
                else {
                    m_spriteAnimator_top.ResetFrame();
                    m_LastEOrientation = m_eOrientation;
                    m_spriteAnimator_top.update(delta);
                }
                break;
            case Tank::EOrientation::Bottom:
                if (m_eOrientation == m_LastEOrientation)
                    m_spriteAnimator_bottom.update(delta);
                else {
                    m_spriteAnimator_bottom.ResetFrame();
                    m_LastEOrientation = m_eOrientation;
                    m_spriteAnimator_bottom.update(delta);
                }
                break;
            case Tank::EOrientation::Left:
                if (m_eOrientation == m_LastEOrientation)
                    m_spriteAnimator_left.update(delta);
                else {
                    m_spriteAnimator_left.ResetFrame();
                    m_LastEOrientation = m_eOrientation;
                    m_spriteAnimator_left.update(delta);
                }
                break;
            case Tank::EOrientation::Right:
                if (m_eOrientation == m_LastEOrientation)
                    m_spriteAnimator_right.update(delta);
                else {
                    m_spriteAnimator_right.ResetFrame();
                    m_LastEOrientation = m_eOrientation;
                    m_spriteAnimator_right.update(delta);
                }
                break;
            }
            
        }
    }
}

void Tank::setVelocity(const double& velocity)
{
    if (!m_isSpawning)
    {
        m_velocity = velocity;
    }
}
