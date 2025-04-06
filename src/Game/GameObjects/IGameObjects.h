#pragma once
#include "external/glm/vec2.hpp"
#include "../../Physics/PhysicsEngine.h"

class IGameObject {
public:

    enum class EtypeOfObject 
    {
        BrickWall,
        BetonWall,
        Border,
        Bullet,
        Water,
        Tank,
        Eagle,
        Trees,
        Ice,

        Unknown
    };

    IGameObject(const EtypeOfObject& type,const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
    virtual void Render() const = 0;
    virtual void update(const double& delta) {};
    virtual ~IGameObject();
    glm::vec2& getCurrentPosition() { return m_position; }
    glm::vec2& getCurrentDirection() { return m_direction; }
    double& getCurrentVelocity() { return m_velocity; }
    float& getCurrentRotation() { return m_rotation; }
    const glm::vec2& getSize() { return m_size; }
    virtual void setVelocity(const double& velocity) { m_velocity = velocity;}
    virtual bool checkColiders(EtypeOfObject typeOfObjectToCheck) { return true; };
    virtual void onCollisionDynamic() {};
    virtual void onCollisionStatic(const std::shared_ptr<IGameObject>& object, const uint8_t& location, const Physics::PhysicsEngine::EDirection& direction) {};
    EtypeOfObject getObjectType() const { return m_objectType; }
    const std::vector<Physics::AABB>& getColliders() const { return m_colliders; };

protected:
    EtypeOfObject m_objectType;
    glm::vec2 m_position;
    glm::vec2 m_size;
    float m_rotation;
    float m_layer;

    glm::vec2 m_direction;
    double m_velocity;
    std::vector<Physics::AABB> m_colliders;
};
