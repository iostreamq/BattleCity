#include "PhysicsEngine.h"
#include "../Game/GameObjects/IGameObjects.h"


namespace Physics
{
	// можно сказать здесь я просто преобразую физические свойства объектов
	std::unordered_set<std::shared_ptr<IGameObject>> PhysicsEngine::m_dynamicObjects;
	std::shared_ptr<Level> PhysicsEngine::m_pCurrentLevel;

	////////////////////////////////////////////////////////////////////////////////UNORD SET///////////////////////////////////////////////////////////////////////////////////////
	void PhysicsEngine::init()
	{
	}

	void PhysicsEngine::terminate()
	{
		m_dynamicObjects.clear(); // уничтожаем поинтеры до уничтожения openGL контекста
		m_pCurrentLevel.reset();
	}

	void PhysicsEngine::update(const double& delta)
	{
		for (auto& currentObject : m_dynamicObjects)
		{
			if (currentObject->getCurrentVelocity() > 0)
			{
				
				float velocity = static_cast<float>(currentObject->getCurrentVelocity());
				const auto newPosition = currentObject->getCurrentPosition() + static_cast<float>(delta) * velocity * currentObject->getCurrentDirection();
				const auto& colliders = currentObject->GetColliders();
				std::vector<std::shared_ptr<IGameObject>> objectsToCheck = m_pCurrentLevel->getObjectsInArea(newPosition, newPosition + currentObject->getSize());
				currentObject->getCurrentPosition() += static_cast<float>(delta) * velocity * currentObject->getCurrentDirection();
			}
		}
	}

	void PhysicsEngine::addDynamicGameObject(std::shared_ptr<IGameObject> pGameObject)
	{
		m_dynamicObjects.insert(std::move(pGameObject));
	}

	void PhysicsEngine::setCurrentLevel(std::shared_ptr<Level> pLevel)
	{
		m_pCurrentLevel = std::move(pLevel);
	}
}