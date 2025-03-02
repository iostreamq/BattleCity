#pragma once
#include "external/glm/vec2.hpp"

class IGameObject {
public:
    IGameObject(const glm::vec2& position, const glm::vec2& size, const float rotation);
    virtual void Render() const = 0;
    virtual void update(const uint64_t& delta) {};
    virtual ~IGameObject();

protected:
    glm::vec2 m_position;
    glm::vec2 m_size;
    float m_rotation;
};
