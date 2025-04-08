#pragma once
#include <cstdint>

class GameState
{
public:
	enum class EGameStates : uint8_t
   {
		Start,
		Level,
		End
   };

	GameState(EGameStates state) :
		m_GameState(state)
	{}
	virtual void Render() const = 0;
	virtual void update(const double delta) = 0;
private:
	EGameStates m_GameState;
};