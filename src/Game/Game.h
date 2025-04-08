#pragma once
#include <array>
#include "external/glm/vec2.hpp"
#include <memory>

class Tank;
class GameState;
class StartScreen;
class Level;

namespace RenderEngine
{
	class Texture2D;
	class Sprite;
    class ShaderProgram;
}

class Game {
public:
	enum class EGameState : uint8_t {
		Start,
		Level,
		End
	};

	Game(const glm::ivec2& windowSize); 
	~Game();

	bool m_canFire = false;
	void Render();
	void update(const double delta);
	void setKey(const int key,const int action);
	bool init(); // инициализация игры подгрузка всех ресов
	size_t GetCurrentLevelWidth() const;
	size_t GetCurrentLevelHeight() const;
	static std::array<bool, 349> m_keys;
	static EGameState m_CurrentGameState;

private:
	glm::ivec2 m_windowSize;
	std::shared_ptr<StartScreen> m_pStartScreen;
	std::shared_ptr<Level> m_pLevel;
	std::shared_ptr<RenderEngine::ShaderProgram> pSpriteShaderProgram;
};