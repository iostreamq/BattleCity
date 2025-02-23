#include "Levels.h"
#include "../Resources/ResourceManager.h"
#include "GameObjects/BrickWall.h"
#include <iostream>

const unsigned int BLOCK_SIZE = 16;

std::shared_ptr<IGameObject> createGameObjectFromDescription(const char description, const glm::vec2& position, const glm::vec2& size, const float rotation)
{
    switch (description)
    {
    case '0':
        return std::make_shared<BrickWall>(ResourceManager::getSprite("brickWall_right"), position, size, rotation);
    case '1':
        return std::make_shared<BrickWall>(ResourceManager::getSprite("brickWall_bottom"), position, size, rotation);
    case '2':
        return std::make_shared<BrickWall>(ResourceManager::getSprite("brickWall_left"), position, size, rotation);
    case '3':
        return std::make_shared<BrickWall>(ResourceManager::getSprite("brickWall_top"), position, size, rotation);
    case '4':
        return std::make_shared<BrickWall>(ResourceManager::getSprite("brickWall"), position, size, rotation);
    case '9':
        return std::make_shared<BrickWall>(ResourceManager::getSprite("betonWall"), position, size, rotation);
    case '8':
        return std::make_shared<BrickWall>(ResourceManager::getSprite("betonWall_top"), position, size, rotation);
    case 'G':
        return std::make_shared<BrickWall>(ResourceManager::getSprite("brickWall_bottom_left"), position, size, rotation);
    case 'H':
        return std::make_shared<BrickWall>(ResourceManager::getSprite("brickWall_bottom_right"), position, size, rotation);
    case 'I':
        return std::make_shared<BrickWall>(ResourceManager::getSprite("brickWall_top_left"), position, size, rotation);
    case 'J':
        return std::make_shared<BrickWall>(ResourceManager::getSprite("brickWall_top_right"), position, size, rotation);
    case 'E':
        return std::make_shared<BrickWall>(ResourceManager::getSprite("eagle"), position, size, rotation);
    case 'D':
        return nullptr;
    default:
        std::cerr << "Unknown GameObject description: " << description << std::endl;
    }
    return nullptr;
}


Level::Level(const std::vector<std::string>& levelDescription)
{
    if (levelDescription.empty())
    {
        std::cerr << "Empty level description!" << std::endl;
    }

    m_width = levelDescription[0].length();
    m_height = levelDescription.size();

    m_levelObjects.reserve(m_width * m_height);
    unsigned int currentBottomOffset = static_cast<unsigned int>(BLOCK_SIZE * (m_height - 1));  //////////////////////////////////////////////
    for (const std::string& currentRow : levelDescription)
    {
        unsigned int currentLeftOffset = 0;
        for (const char currentElement : currentRow)
        {
            m_levelObjects.emplace_back(createGameObjectFromDescription(currentElement, glm::vec2(currentLeftOffset, currentBottomOffset), glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0.f));
            currentLeftOffset += BLOCK_SIZE;
        }
        currentBottomOffset -= BLOCK_SIZE;
    }
}

void Level::Render() const
{
    for (const auto& currentLevelObject : m_levelObjects)
    {
        if (currentLevelObject)
        {
            currentLevelObject->Render();
        }
    }
}

void Level::update(const uint64_t delta)
{
    for (const auto& currentLevelObject : m_levelObjects)
    {
        if (currentLevelObject)
        {
            currentLevelObject->update(delta);
        }
    }
}
