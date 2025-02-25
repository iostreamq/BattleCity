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

void Game::update(const uint64_t delta)
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
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_A])
        {
            m_pTank->setOrientation(Tank::EOrientation::Left);
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_D])
        {
            m_pTank->setOrientation(Tank::EOrientation::Right);
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_S])
        {
            m_pTank->setOrientation(Tank::EOrientation::Bottom);
            m_pTank->move(true);
        }
        else
        {
            m_pTank->move(false);
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
  
   auto pTextureAtas = ResourceManager::getTexture("mapTextureAtlas");
   if (!pTextureAtas) {
       std::cerr << "Can`t find atlas" << "mapTextureAtlas" << std::endl;
       return false;
   }

   auto pTanksTextureAtas = ResourceManager::getTexture("TanksTextureAtlas");
   if (!pTanksTextureAtas) {
       std::cerr << "Can`t find Tank`s atlas" << "TanksTextureAtlas" << std::endl;
       return false;
   }



    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f); // ортографическая матрица передаем характеристики фрустона // static_cast<float>

    pSpriteShaderProgram->use(); 
    pTextureAtas->bind();////////////////////////////////////////////////////////////////////////
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix4("projectionMatrix", projectionMatrix);
 
    
    m_pTank = std::make_unique<Tank>(ResourceManager::getSprite("tankSprite_top")
                                   , ResourceManager::getSprite("tankSprite_bottom")
                                   , ResourceManager::getSprite("tankSprite_left")
                                   , ResourceManager::getSprite("tankSprite_right")
        , 0.0000001f, glm::vec2(0), glm::vec2(16.f, 16.f));
    m_pLevel = std::make_unique<Level>(ResourceManager::getLevels()[0]);

    return true;
}
