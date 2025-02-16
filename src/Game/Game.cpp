#include "Game.h"
#include "../Resources/ResourceManager.h" /////// почему не подключаются заголовки manager`a
#include "../Renderer/ShaderProgram.h" 
#include "../Renderer/Texture2D.h" 
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<string>
#include "external/glm/vec2.hpp"
#include "external/glm/mat4x4.hpp"
#include "external/glm/gtc/matrix_transform.hpp"
#include "../Game/Tank.h"



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
    //ResourceManager::getAnimatedSprite("DefaultAnimatedSprite")->Render();
    if (m_pTank)
    {

        m_pTank->Render();
    }
}

void Game::update(const uint64_t delta)
{
    // ResourceManager::getAnimatedSprite("DefaultAnimatedSprite")->update(delta);

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


    auto pAnimatedSprite = ResourceManager::loadAnimatedSprites("DefaultAnimatedSprite", "mapTextureAtlas", "SpriteShaderProgram", 100, 100, "beton");
    pAnimatedSprite->setPosition(glm::vec2(300, 300));
    std::vector<std::pair<std::string, uint64_t>> waterState;
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water1", 1000000000));
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water2", 1000000000));
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water3", 1000000000));

    std::vector<std::pair<std::string, uint64_t>> eagleState;
    eagleState.emplace_back(std::make_pair<std::string, uint64_t>("eagle", 1000000000));
    eagleState.emplace_back(std::make_pair<std::string, uint64_t>("deadEagle", 1000000000));

    pAnimatedSprite->insertState("waterState", std::move(waterState));
    pAnimatedSprite->insertState("eagleState", std::move(eagleState));

    pAnimatedSprite->setState("waterState");

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f); // ортографическая матрица передаем характеристики фрустона // static_cast<float>

    pSpriteShaderProgram->use(); 
    pTextureAtas->bind();////////////////////////////////////////////////////////////////////////
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix4("projectionMatrix", projectionMatrix);
 
    auto pTanksAnimatedSprite = ResourceManager::getAnimatedSprite("TanksAnimatedSprite");
    if (!pTanksAnimatedSprite) 
    {
        std::cerr << "Can`t find animated sprite" << "TanksAnimatedSprite" << std::endl;
        return false;
    }
    
    m_pTank = std::make_unique<Tank>(pTanksAnimatedSprite, 0.0000001f, glm::vec2(100.f,100.f)); ///////////////////////////////////////////////////////
    return true;
}
