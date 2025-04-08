#pragma once
#include "GameState.h"
#include <vector>
#include <memory>

namespace RenderEngine { class Sprite; class Texture2D; }
class Tank;

class StartScreen : public GameState
{
public:
	StartScreen(std::shared_ptr<Tank> _m_pTank);
	virtual void Render() const override;
	virtual void update(const double delta) override;
private:
	std::vector<std::shared_ptr<RenderEngine::Sprite>> m_startScreen;
	std::shared_ptr<RenderEngine::Texture2D> m_battleCityTexture;
	std::shared_ptr<Tank> m_pTank;
};