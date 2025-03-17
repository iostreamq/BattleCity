#pragma once
#include "external/glm/vec2.hpp"
#include "../../Physics/PhysicsEngine.h"

class IGameObject {
public:
    IGameObject(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
    virtual void Render() const = 0;
    virtual void update(const double& delta) {};
    virtual ~IGameObject();
    glm::vec2& getCurrentPosition() { return m_position; }
    glm::vec2& getCurrentDirection() { return m_direction; }
    double& getCurrentVelocity() { return m_velocity; }
    const glm::vec2& getSize() { return m_size; }
    virtual void setVelocity(const double& velocity) { m_velocity = velocity;}

    const std::vector<Physics::AABB>& getColliders() const { return m_colliders; };

protected:
    glm::vec2 m_position;
    glm::vec2 m_size;
    float m_rotation;
    float m_layer;

    glm::vec2 m_direction;
    double m_velocity;
    std::vector<Physics::AABB> m_colliders;
};
