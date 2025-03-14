#pragma once
#include <array>
#include "external/glm/vec2.hpp"
#include <memory>
#include "Levels.h"

class Tank;

class Game {
public:
	Game(const glm::ivec2& windowSize); 
	~Game();


	void Render();
	void update(const double delta);
	void setKey(const int key,const int action);
	bool init(); // инициализация игры подгрузка всех ресов
	size_t GetCurrentLevelWidth() const;
	size_t GetCurrentLevelHeight() const;
	
private:
	std::array<bool, 349> m_keys;
	enum class EGameState : uint8_t {
		Active,
		Pause
	};

	EGameState m_CurrentGameState;
	glm::ivec2 m_windowSize;
	std::shared_ptr<Tank> m_pTank; 
 	std::shared_ptr<Level> m_pLevel;

};