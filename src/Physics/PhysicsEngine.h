#pragma once
#include <unordered_set>
#include <memory>
#include "../Game/Levels.h"

class IGameObject;

namespace Physics 
{
	struct AABB
	{
		glm::vec2 bottomLeft;
		glm::vec2 rightTop;
	
		AABB(const glm::vec2& _bottomLeft, const glm::vec2& _rightTop) :
			bottomLeft(_bottomLeft)
			, rightTop(_rightTop)
		{}
	};

	class PhysicsEngine {

	public:
		~PhysicsEngine() = delete;
		PhysicsEngine() = delete;
		PhysicsEngine(const PhysicsEngine&) = delete;
		PhysicsEngine& operator=(const PhysicsEngine&) = delete;
		PhysicsEngine(PhysicsEngine&&) = delete;
		PhysicsEngine& operator=(PhysicsEngine&&) = delete;

		static void init();
		static void terminate();
		static void update(const double& delta);
		static  void addDynamicGameObject(std::shared_ptr<IGameObject> pGameObject);
		static void setCurrentLevel(std::shared_ptr<Level> pLevel);
	private:
		static std::unordered_set<std::shared_ptr<IGameObject>> m_dynamicObjects;
		static std::shared_ptr<Level> m_pCurrentLevel;
	};
};

