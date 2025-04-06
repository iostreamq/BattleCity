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

		AABB(const glm::vec2& _nothing) 		
		{}
	};

	class PhysicsEngine {

	public:

		enum class EDirection
		{
			Top,
			Bottom,
			Left,
            Right
		};

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
		static EDirection StaticObjectDirection;
		static bool hasIntersections(const glm::vec2& dynamicObjectPosition,
		const std::shared_ptr<IGameObject>& dynamicObject,
		std::vector<std::shared_ptr<IGameObject>> staticObjectsToCheck);

		static std::unordered_set<std::shared_ptr<IGameObject>> m_dynamicObjects;
		static std::shared_ptr<Level> m_pCurrentLevel;
	};
};

