#include "Game.h"
#include "../Resources/ResourceManager.h" /////// почему не подключаются заголовки manager`a
#include "../Renderer/ShaderProgram.h" 
#include "../Renderer/Texture2D.h" 
#include "../Renderer/Sprite.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<string>

#include "external/glm/vec2.hpp"
#include "external/glm/mat4x4.hpp"
#include "external/glm/gtc/matrix_transform.hpp"

#include "../Game/GameObjects/Tank.h"
#include "../Physics/PhysicsEngine.h"
#include "GameState/Levels.h"
#include "GameState/StartScreen.h"
#include "GameState/GameState.h"

std::array<bool, 349> Game::m_keys;
Game::EGameState Game::m_CurrentGameState = EGameState::Start;

Game::Game(const glm::ivec2& windowSize) :
    m_windowSize(windowSize)
{
	m_keys.fill(false); // когда игра стартует не одна клавиша не нажата
}

Game::~Game()
{

}

void Game::Render()
{
    if (m_CurrentGameState == EGameState::Start)
    {
        if (m_pStartScreen)
        {
            m_pStartScreen->Render();
        }
    }

    else if (m_pLevel)
    {
       m_pLevel->Render();
    }
}

void Game::update(const double delta)
{
   
    if (m_keys[GLFW_KEY_ENTER] && m_pLevel->GetTank()->getCurrentChoice() == 1)
    {
        m_CurrentGameState = EGameState::Level;
        m_pStartScreen->update(delta);
    }
    if (m_CurrentGameState == EGameState::Start)
    {
        if (m_pStartScreen)
        {
            m_pStartScreen->update(delta);
        }
    }

    else if (m_pLevel)
    {
        m_pLevel->update(delta);
    }
    
 }


void Game::setKey(const int key, const int action)
{
	m_keys[key] = action; // нажимаю клавишу- тру отжимаю - фолз
}

bool Game::init()
{
    ResourceManager::loadJSONResources("/res/resources.json");
    pSpriteShaderProgram =  ResourceManager::getShaderProgram("SpriteShaderProgram");
    if (!pSpriteShaderProgram) {
        std::cerr << "Can`t find ShadeProgram" << "pSpriteShaderProgram" << std::endl;
        return false;
    }
    
    m_pLevel = std::make_shared<Level>(ResourceManager::getLevels()[0]);
    m_pStartScreen = std::make_shared<StartScreen>(m_pLevel->GetTank());
    m_windowSize.x = static_cast<int>(m_pLevel->GetLevelWidth());
    m_windowSize.y = static_cast<int>(m_pLevel->GetLevelHeight());
    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f); // ортографическая матрица передаем характеристики фрустона // static_cast<float>
    Physics::PhysicsEngine::setCurrentLevel(m_pLevel);
    
   
    pSpriteShaderProgram->use(); 
    pSpriteShaderProgram->setInt("tex", 0);  
    pSpriteShaderProgram->setMatrix4("projectionMatrix", projectionMatrix);

    return true;
}

size_t Game::GetCurrentLevelWidth() const
{
    return m_pLevel->GetLevelWidth();
}

size_t Game::GetCurrentLevelHeight() const
{
    return  m_pLevel->GetLevelHeight();
}
