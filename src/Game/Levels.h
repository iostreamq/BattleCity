#pragma once
#include <vector>
#include <string>
#include <memory>
#include "external/glm/vec2.hpp"

class IGameObject;

class Level {
public:
    static constexpr unsigned int BLOCK_SIZE = 16;

    Level(const std::vector<std::string>& levelDescription);
    void Render() const;
    void update(const double delta);
    size_t GetLevelWidth()  const;
    size_t GetLevelHeight() const;
    const glm::ivec2& GetPlayerRespawn_1() const { return m_playerRespawn_1; }
    const glm::ivec2& GetPlayerRespawn_2() const { return m_playerRespawn_2; }
    const glm::ivec2& GetEnemyRespawn_1() const { return m_enemyRespawn_1; }
    const glm::ivec2& GetEnemyRespawn_2() const { return m_enemyRespawn_2; }
    const glm::ivec2& GetEnemyRespawn_3() const { return m_enemyRespawn_3; }
    std::vector<std::shared_ptr<IGameObject>> getObjectsInArea(const glm::vec2& bottomLeft, const glm::vec2& topRight);

private:
    size_t m_widthBlocks = 0;
    size_t m_heightBlocks = 0;
    unsigned int m_widthPixels = 0;
    unsigned int m_heightPixels = 0;
    glm::ivec2 m_playerRespawn_1;
    glm::ivec2 m_playerRespawn_2;
    glm::ivec2 m_enemyRespawn_1;
    glm::ivec2 m_enemyRespawn_2;
    glm::ivec2 m_enemyRespawn_3;
    std::vector<std::shared_ptr<IGameObject>> m_levelObjects;
};
