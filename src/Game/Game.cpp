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
#include "Levels.h"



Game::Game(const glm::ivec2& windowSize):
    m_CurrentGameState(EGameState::Active),
    m_windowSize(windowSize)
{
	m_keys.fill(false); // когда игра стартует не одна клавиша не нажата
}

Game::~Game()
{

}

void Game::Render()
{
    if (m_pTank)
    {
        m_pTank->Render();
    }

    if (m_pLevel)
    {
        m_pLevel->Render();
    }
}

void Game::update(const double delta)
{
    if (m_pLevel)
    {
        m_pLevel->update(delta);
    }

    if (m_pTank)
    {
        if (m_keys[GLFW_KEY_W])
        {
            m_pTank->setOrientation(Tank::EOrientation::Top);
            m_pTank->setVelocity(m_pTank->GetMaxVelocity());
           
        }
        else if (m_keys[GLFW_KEY_A])
        {
            m_pTank->setOrientation(Tank::EOrientation::Left);
            m_pTank->setVelocity(m_pTank->GetMaxVelocity());
    
        }
        else if (m_keys[GLFW_KEY_D])
        {
            m_pTank->setOrientation(Tank::EOrientation::Right);
            m_pTank->setVelocity(m_pTank->GetMaxVelocity());
        }
        else if (m_keys[GLFW_KEY_S])
        {
            m_pTank->setOrientation(Tank::EOrientation::Bottom);
            m_pTank->setVelocity(m_pTank->GetMaxVelocity());
        }
        else
        {
            m_pTank->setVelocity(0.f);
        }

        m_pTank->update(delta);
    }
}


void Game::setKey(const int key, const int action)
{
	m_keys[key] = action; // нажимаю клавишу- тру отжимаю - фолз
}

bool Game::init()
{
    ResourceManager::loadJSONResources("/res/resources.json");
    std::shared_ptr<RenderEngine::ShaderProgram>pSpriteShaderProgram =  ResourceManager::getShaderProgram("SpriteShaderProgram");
    if (!pSpriteShaderProgram) {
        std::cerr << "Can`t find ShadeProgram" << "pSpriteShaderProgram" << std::endl;
        return false;
    }
    m_pLevel = std::make_shared<Level>(ResourceManager::getLevels()[0]);
    m_windowSize.x = static_cast<int>(m_pLevel->GetLevelWidth());
    m_windowSize.y = static_cast<int>(m_pLevel->GetLevelHeight());
    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f); // ортографическая матрица передаем характеристики фрустона // static_cast<float>
    Physics::PhysicsEngine::setCurrentLevel(m_pLevel);

    pSpriteShaderProgram->use(); 
    pSpriteShaderProgram->setInt("tex", 0);  
    pSpriteShaderProgram->setMatrix4("projectionMatrix", projectionMatrix);
 
    m_pTank = std::make_shared<Tank>(0.05, m_pLevel->GetPlayerRespawn_2(), glm::vec2(Level::BLOCK_SIZE, Level::BLOCK_SIZE), 0.f);
    Physics::PhysicsEngine::addDynamicGameObject(m_pTank);
    //PhysicsEngine::addDynamicGameObject(m_pLevel);

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
