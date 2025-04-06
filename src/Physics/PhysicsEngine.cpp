#include "PhysicsEngine.h"
#include "../Game/GameObjects/IGameObjects.h"
#include <iostream>
#include <cmath>

std::unordered_set<std::shared_ptr<IGameObject>> Physics::PhysicsEngine::m_dynamicObjects;
std::shared_ptr<Level>  Physics::PhysicsEngine::m_pCurrentLevel;
Physics::PhysicsEngine::EDirection Physics::PhysicsEngine::StaticObjectDirection;

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

    for (const auto& currentDynamicObject : m_dynamicObjects)
    {
            if (currentDynamicObject->getCurrentVelocity() > 0)
        {

            if (currentDynamicObject->getCurrentDirection().x != 0.f)
            {
                currentDynamicObject->getCurrentPosition() = glm::vec2(currentDynamicObject->getCurrentPosition().x,
                    static_cast<unsigned int>(currentDynamicObject->getCurrentPosition().y / 4.f + 0.5f) * 4);
            }

            else if (currentDynamicObject->getCurrentDirection().y != 0.f)
            {
                currentDynamicObject->getCurrentPosition() = glm::vec2(static_cast<unsigned int>(currentDynamicObject->getCurrentPosition().x / 4.f + 0.5f) * 4,
                 currentDynamicObject->getCurrentPosition().y
             ); 

            }
            auto newPosition = currentDynamicObject->getCurrentPosition() + static_cast<float>(delta * currentDynamicObject->getCurrentVelocity()) * currentDynamicObject->getCurrentDirection();
            const auto vectorOfObjectsToCheck = m_pCurrentLevel->getObjectsInArea(newPosition, currentDynamicObject->getSize() + newPosition);
        
            EDirection DynamicObjectDirection = EDirection::Right;
            if (currentDynamicObject->getCurrentDirection().x < 0) DynamicObjectDirection = EDirection::Left;
            else if (currentDynamicObject->getCurrentDirection().y > 0) DynamicObjectDirection = EDirection::Top;
            else if (currentDynamicObject->getCurrentDirection().y < 0) DynamicObjectDirection = EDirection::Bottom;

            StaticObjectDirection = EDirection::Left;
            if (DynamicObjectDirection == EDirection::Left) StaticObjectDirection = EDirection::Right;
            else if (DynamicObjectDirection == EDirection::Top) StaticObjectDirection = EDirection::Bottom;
            else if (DynamicObjectDirection == EDirection::Bottom) StaticObjectDirection = EDirection::Top;

           //наверно времен логика пока не так много накладных расходов на это все 

            std::vector<std::shared_ptr<IGameObject>> filteredObjects;
            filteredObjects.reserve(vectorOfObjectsToCheck.size());

            for (const auto& obj : vectorOfObjectsToCheck) 
            {
                if (currentDynamicObject->checkColiders(obj->getObjectType()))
                {
                    filteredObjects.emplace_back(obj);
                }
            }

            bool hasCollisions = hasIntersections(newPosition, currentDynamicObject, filteredObjects);

            if (!hasCollisions) currentDynamicObject->getCurrentPosition() = newPosition;
            
            else 
            {
                if (currentDynamicObject->getCurrentDirection().x != 0.f) // right and left
                {
                    currentDynamicObject->getCurrentPosition() = glm::vec2(static_cast<unsigned int>(currentDynamicObject->getCurrentPosition().x / 4.f + 0.5f) * 4, currentDynamicObject->getCurrentPosition().y);
                    
                }
                else if (currentDynamicObject->getCurrentDirection().y != 0.f) // top and bottom
                {
                    currentDynamicObject->getCurrentPosition() = glm::vec2(currentDynamicObject->getCurrentPosition().x, static_cast<unsigned int>(currentDynamicObject->getCurrentPosition().y / 4.f + 0.5f) * 4);
                }
               
                currentDynamicObject->onCollisionDynamic();
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
    const std::shared_ptr<IGameObject>& dynamicObject,
    std::vector<std::shared_ptr<IGameObject>> staticObjectsToCheck)
{
    glm::vec2 colliderTankrightTop = dynamicObjectPosition + dynamicObject->getColliders()[0].rightTop;
    glm::vec2 colliderTankLeftBottom = dynamicObjectPosition + dynamicObject->getColliders()[0].bottomLeft;

    if (!staticObjectsToCheck.empty())
    {
        for (const auto& currentObject : staticObjectsToCheck)
        {
            if (!currentObject->getColliders().empty())
            {
                uint8_t countCollider = -1;
                for (const auto& currentCollider : currentObject->getColliders())
                {
                    countCollider++;
                    glm::vec2 colliderObjectLeftBottom = currentObject->getCurrentPosition() + currentCollider.bottomLeft;
                    glm::vec2 colliderObjectRightTop = currentObject->getCurrentPosition() + currentCollider.rightTop;

                    if (colliderTankrightTop.x <= colliderObjectLeftBottom.x)
                        continue;

                    else if (colliderTankLeftBottom.x >= colliderObjectRightTop.x)
                        continue;

                    else if (colliderTankLeftBottom.y >= colliderObjectRightTop.y)
                        continue;

                    else if (colliderTankrightTop.y <= colliderObjectLeftBottom.y)
                        continue;

                    else
                    {
                        currentObject->onCollisionStatic(dynamicObject,countCollider, StaticObjectDirection);
                        return true;
                    }
                 }

            }
        }
    }

    return false;
}