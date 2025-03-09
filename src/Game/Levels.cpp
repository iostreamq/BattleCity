#include "Levels.h"
#include "GameObjects/BrickWall.h"
#include "GameObjects/BetonWall.h"
#include "GameObjects/Trees.h"
#include "GameObjects/Ice.h"
#include "GameObjects/Water.h"
#include "GameObjects/Border.h"
#include "GameObjects/Eagle.h"
#include <iostream>
#include <algorithm>





std::shared_ptr<IGameObject> createGameObjectFromDescription(const char description, const glm::vec2& position, const glm::vec2& size, const float rotation)
{
    switch (description)
    {
    case '0':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Right, position, size, rotation, 0.f);
    case '1':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Bottom, position, size, rotation, 0.f);
    case '2':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Left, position, size, rotation, 0.f);
    case '3':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Top, position, size, rotation, 0.f);
    case '4':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::All, position, size, rotation, 0.f);
    case '9':
        return std::make_shared<BetonWall>(BetonWall::EBetonWallType::All, position, size, rotation, 0.f);
    case '5':
        return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Right, position, size, rotation, 0.f);
    case '6':   
        return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Bottom, position, size, rotation, 0.f);
    case '7':
        return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Left, position, size, rotation, 0.f);
    case '8':
        return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Top, position, size, rotation, 0.f);
    case 'G':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::BottomLeft, position, size, rotation, 0.f);
    case 'H':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::BottomRight, position, size, rotation, 0.f);
    case 'I':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::TopLeft, position, size, rotation, 0.f);
    case 'J':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::TopRight, position, size, rotation, 0.f);
    case 'A':
        return std::make_shared<Water>(position, size, rotation, 0.f);
    case 'B':
        return std::make_shared<Trees>(position, size, rotation, 1.f);
    case 'C':
        return std::make_shared<Ice>(position, size, rotation, -1.f);
        case 'E':
        return std::make_shared<Eagle>(position, size, rotation, 0.f);
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

    m_widthBlocks = levelDescription[0].length();
    m_heightBlocks = levelDescription.size();
    m_widthPixels = m_widthBlocks * BLOCK_SIZE;
    m_heightPixels = m_heightBlocks * BLOCK_SIZE;
    m_playerRespawn_1 = { BLOCK_SIZE * (m_widthBlocks/2-1), BLOCK_SIZE/2};
    m_playerRespawn_2 = { BLOCK_SIZE * (m_widthBlocks/2+3), BLOCK_SIZE/2}; ////////////////////////
    m_enemyRespawn_1 = { BLOCK_SIZE, BLOCK_SIZE * m_heightBlocks - BLOCK_SIZE / 2 };
    m_enemyRespawn_2 = { BLOCK_SIZE  * ((m_widthBlocks + 1) / 2), BLOCK_SIZE * m_heightBlocks - BLOCK_SIZE / 2 };
    m_enemyRespawn_3 = { BLOCK_SIZE * m_widthBlocks, BLOCK_SIZE * m_heightBlocks - BLOCK_SIZE / 2 };


    m_levelObjects.reserve(m_widthBlocks * m_heightBlocks + 4);
    unsigned int currentBottomOffset = static_cast<unsigned int>(BLOCK_SIZE * (m_heightBlocks - 1) + BLOCK_SIZE/2.f);  //////////////////////////////////////////////
    for (const std::string& currentRow : levelDescription)
    {
        unsigned int currentLeftOffset = BLOCK_SIZE;
        for (const char currentElement : currentRow)
        {
            switch (currentElement)
            {
            case 'K':
                m_playerRespawn_1 = { currentLeftOffset, currentBottomOffset };
                break;
            case 'L':
                m_playerRespawn_2 = { currentLeftOffset, currentBottomOffset };
                break;
            case 'M':
                m_enemyRespawn_1 = { currentLeftOffset, currentBottomOffset };
                break;
            case 'N':
                m_enemyRespawn_2 = { currentLeftOffset, currentBottomOffset };
                break;
            case 'O':
                m_enemyRespawn_3 = { currentLeftOffset, currentBottomOffset };
                break;
            default:
                m_levelObjects.emplace_back(createGameObjectFromDescription(currentElement, glm::vec2(currentLeftOffset, currentBottomOffset), glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0.f));
                break;
            }   
            currentLeftOffset += BLOCK_SIZE;
        }
        currentBottomOffset -= BLOCK_SIZE;
    }
    //bottom border
    m_levelObjects.emplace_back(std::make_shared<Border>(glm::vec2(BLOCK_SIZE, 0.f), glm::vec2(m_widthBlocks * BLOCK_SIZE, BLOCK_SIZE / 2.f), 0.f, 0.f));
    //border top
    m_levelObjects.emplace_back(std::make_shared<Border>(glm::vec2(BLOCK_SIZE, (m_heightBlocks*16)+(BLOCK_SIZE/2)), glm::vec2(m_widthBlocks * BLOCK_SIZE, BLOCK_SIZE / 2.f), 0.f, 0.f));/////////////////
    //border left
    m_levelObjects.emplace_back(std::make_shared<Border>(glm::vec2(0.f, 0.f), glm::vec2(BLOCK_SIZE, BLOCK_SIZE * (m_heightBlocks+2)), 0.f, 0.f));
    //border right
    m_levelObjects.emplace_back(std::make_shared<Border>(glm::vec2((1+m_widthBlocks)*BLOCK_SIZE, 0.f), glm::vec2(2.f * BLOCK_SIZE, BLOCK_SIZE * (m_heightBlocks + 2)), 0.f, 0.f));

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

void Level::update(const double delta)
{
    for (const auto& currentLevelObject : m_levelObjects)
    {
        if (currentLevelObject)
        {
            currentLevelObject->update(delta);
        }
    }
}

size_t Level::GetLevelWidth() const
{
    return (m_widthBlocks + 3) * BLOCK_SIZE;
}

size_t Level::GetLevelHeight() const
{
    return(m_heightBlocks + 1) * BLOCK_SIZE;
}

    std::vector<std::shared_ptr<IGameObject>> Level::getObjectsInArea(const glm::vec2& bottomLeft, const glm::vec2& topRight)
{
    std::vector<std::shared_ptr<IGameObject>> output;
    output.reserve(9);  

 
    glm::vec2 bottomleft_converted(std::clamp(bottomLeft.x - BLOCK_SIZE, 0.f, static_cast<float>(m_widthPixels)),
                                   std::clamp(m_widthBlocks * BLOCK_SIZE - bottomLeft.y + BLOCK_SIZE / 2, 0.f, static_cast<float>(m_heightPixels)));
    glm::vec2 topRight_converted(std::clamp(topRight.x - BLOCK_SIZE, 0.f, static_cast<float>(m_widthPixels)),
                                 std::clamp(m_widthBlocks * BLOCK_SIZE - topRight.y + BLOCK_SIZE / 2, 0.f, static_cast<float>(m_heightPixels)));
    
    std::cout << "bottomleft_converted.x: " << bottomleft_converted.x << "bottomleft_converted.y: " << bottomleft_converted.y << std::endl;
    std::cout << "topRight_converted.x: " << topRight_converted.x << "topRight_converted.y: " << topRight_converted.y << std::endl;
    
    return output;
}
