#include "StartScreen.h"
#include "../../Resources/ResourceManager.h"
#include "../GameObjects/Tank.h"
#include "../Game.h"

StartScreen::StartScreen(std::shared_ptr<Tank> _m_pTank)
	:GameState(EGameStates::Start)
	, m_battleCityTexture(ResourceManager::getTexture("BattleCity"))
    , m_pTank(_m_pTank)
{
    m_battleCityTexture->addSubTexture("BattleCityName", glm::vec2(0.0625f, 0.51f), glm::vec2(1.f));
    m_battleCityTexture->addSubTexture("BattleCityMenu", glm::vec2(0.31f, 0.25f), glm::vec2(0.8f, 0.48f));
    m_battleCityTexture->addSubTexture("BattleCityHz", glm::vec2(0.1f, 0.f), glm::vec2(0.8f, 0.25f));
    m_startScreen.emplace_back(std::make_shared<RenderEngine::Sprite>(m_battleCityTexture, "BattleCityName", ResourceManager::getShaderProgram("SpriteShaderProgram")));
    m_startScreen.emplace_back(std::make_shared<RenderEngine::Sprite>(m_battleCityTexture, "BattleCityMenu", ResourceManager::getShaderProgram("SpriteShaderProgram")));
    m_startScreen.emplace_back(std::make_shared<RenderEngine::Sprite>(m_battleCityTexture, "BattleCityHz", ResourceManager::getShaderProgram("SpriteShaderProgram")));
}

void StartScreen::Render() const
{
    for (size_t i = 0; i < m_startScreen.size(); i++)
    {
        if (i == 0) m_startScreen[i]->Render(glm::vec2(30, 100), glm::vec2(200, 150), 0.f);

        if (i == 1) m_startScreen[i]->Render(glm::vec2(90, 50), glm::vec2(70, 40), 0.f);

        if (i == 2) m_startScreen[i]->Render(glm::vec2(50, 10), glm::vec2(120, 35), 0.f);
    }
    m_pTank->Render();
}

void StartScreen::update(const double delta)
{
    if (Game::m_CurrentGameState == Game::EGameState::Start)
        m_pTank->update(delta);

    else m_pTank->GetStartScreen() = false;
}

