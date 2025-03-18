#include "PhysicsEngine.h"
#include "../Game/GameObjects/IGameObjects.h"
#include <iostream>
#include <cmath>

std::unordered_set<std::shared_ptr<IGameObject>> Physics::PhysicsEngine::m_dynamicObjects;
std::shared_ptr<Level>  Physics::PhysicsEngine::m_pCurrentLevel;

void Physics::PhysicsEngine::init()
{
}

void Physics::PhysicsEngine::terminate()
{
    m_dynamicObjects.clear();
    m_pCurrentLevel.reset();
}

void Physics::PhysicsEngine::update(const double& delta)
{

    for (const auto& currentObject : m_dynamicObjects)
    {
        if (currentObject->getCurrentVelocity() > 0)
        {

            if (currentObject->getCurrentDirection().x != 0.f)
            {
                currentObject->getCurrentPosition() = glm::vec2(currentObject->getCurrentPosition().x,
                    static_cast<unsigned int>(currentObject->getCurrentPosition().y / 4.f + 0.5f) * 4);
            }

            else if (currentObject->getCurrentDirection().y != 0.f)
            {
                currentObject->getCurrentPosition() = glm::vec2(static_cast<unsigned int>(currentObject->getCurrentPosition().x / 4.f + 0.5f) * 4,
                 currentObject->getCurrentPosition().y
             ); 

            }
            auto newPosition = currentObject->getCurrentPosition() + static_cast<float>(delta * currentObject->getCurrentVelocity()) * currentObject->getCurrentDirection();
            const auto vectorOfObjectsToCheck = m_pCurrentLevel->getObjectsInArea(newPosition, currentObject->getSize() + newPosition);
        
           //наверно времен логика пока не так много накладных расходов на это все 

            std::vector<std::shared_ptr<IGameObject>> filteredObjects;
            filteredObjects.reserve(vectorOfObjectsToCheck.size());

            for (const auto& obj : vectorOfObjectsToCheck) 
            {
                if (currentObject->checkColiders(obj->getObjectType()))
                {
                    filteredObjects.emplace_back(obj);
                }
            }

            bool hasCollisions = hasIntersections(newPosition, currentObject->getColliders(), filteredObjects);

            if (!hasCollisions) currentObject->getCurrentPosition() = newPosition;
            
            else 
            {
                if (currentObject->getCurrentDirection().x != 0.f) // right and left
                {
                    currentObject->getCurrentPosition() = glm::vec2(static_cast<unsigned int>(currentObject->getCurrentPosition().x / 8.f + 0.5f) * 8, currentObject->getCurrentPosition().y);
                    
                }
                else if (currentObject->getCurrentDirection().y != 0.f) // top and bottom
                {
                    currentObject->getCurrentPosition() = glm::vec2(currentObject->getCurrentPosition().x, static_cast<unsigned int>(currentObject->getCurrentPosition().y / 8.f + 0.5f) * 8);
                }

                currentObject->onCollision();
            }
            
        }
    }
    // colliderTankrightTop.x < colliderObjectLeftBottom.x 
    // colliderTankLeftBottom.x > colliderObjectRightTop.x 
    // colliderTankLeftBottom.y > colliderObjectRightTop.y 
    // colliderTankrightTop.y < colliderObjectLeftBottom.y 
}

void Physics::PhysicsEngine::addDynamicGameObject(std::shared_ptr<IGameObject> pGameObject)
{
    m_dynamicObjects.insert(std::move(pGameObject));
}

void Physics::PhysicsEngine::setCurrentLevel(std::shared_ptr<Level> pLevel)
{
    m_pCurrentLevel = std::move(pLevel);
}

bool Physics::PhysicsEngine::hasIntersections(const glm::vec2& dynamicObjectPosition,
    const std::vector<Physics::AABB>& dynamicObjectColiders,
    std::vector<std::shared_ptr<IGameObject>> staticObjectsToCheck)
{
    glm::vec2 colliderTankrightTop = dynamicObjectPosition + dynamicObjectColiders[0].rightTop;
    glm::vec2 colliderTankLeftBottom = dynamicObjectPosition + dynamicObjectColiders[0].bottomLeft;

    if (!staticObjectsToCheck.empty())
    {
        for (const auto& currentObject : staticObjectsToCheck)
        {
            if (!currentObject->getColliders().empty()) {

                glm::vec2 colliderObjectLeftBottom = currentObject->getCurrentPosition() + currentObject->getColliders()[0].bottomLeft;
                glm::vec2 colliderObjectRightTop = currentObject->getCurrentPosition() + currentObject->getColliders()[0].rightTop;

                if (colliderTankrightTop.x <= colliderObjectLeftBottom.x)
                    continue;

                else if (colliderTankLeftBottom.x >= colliderObjectRightTop.x)
                    continue;

                else if (colliderTankLeftBottom.y >= colliderObjectRightTop.y)
                    continue;

                else if (colliderTankrightTop.y <= colliderObjectLeftBottom.y)
                    continue;

                else return true;
            }
        }
    }

    return false;
}