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
    auto pSpriteShaderProgram = ResourceManager::loadShaders("SpriteShaderProgram", "/res/shaders/vSprite.txt", "/res/shaders/fSprite.txt"); //есть ли разница передавать /res/shaders/vertexShader.txt и res/shaders/vertexShader.txt прост овсе равно потом я добавлю в открытии файла + '/'
    if (pSpriteShaderProgram == nullptr) {

        std::cerr << "Can`t create SpriteShader progam" << std::endl;
        return false;
    }

    auto tex = ResourceManager::loadTexture("DefaultTexture", "/res/textures/map_16x16.png");

    std::vector<std::string> subTexturesNames = { "block",
                                                "topBlock",
                                                "BottomBlock",
                                                "leftBlock",
                                                "rightBlock",
                                                "topLeftBlock",
                                                "topRightBlock",
                                                "bottomLeftBlock",
                                                "bottomRightBlock",

                                                "beton",
                                                "topBeton",
                                                "bottomBeton",
                                                "leftBeton",
                                                "rightBeton",
                                                "topLeftBeton",
                                                "topRightBeton",
                                                "bottomLeftBeton",
                                                "bottomRightBeton",

                                                "water1",
                                                "water2",
                                                "water3",
                                                "trees",
                                                "ice",
                                                "wall",

                                                "eagle",
                                                "deadEagle",
                                                "nothing",
                                                "respawn1",
                                                "respawn2",
                                                "respawn3",
                                                "respawn4" };



    auto pTextureAtas = ResourceManager::loadTextureAtlas("DefaultTextureAtlas", "/res/textures/map_16x16.png", std::move(subTexturesNames), 16, 16);

    auto pAnimatedSprite = ResourceManager::loadAnimatedSprites("DefaultAnimatedSprite", "DefaultTextureAtlas", "SpriteShaderProgram", 100, 100, "beton");
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

    glm::mat4 modelMatrix_1 = glm::mat4(1.f); // матрица в которой по диагонали единицы а в остальных местах нули и такая матрица не совершает преобразований
    modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(50.f, 50.f, 0.f));


    glm::mat4 modelMatrix_2 = glm::mat4(1.f); // матрица в которой по диагонали единицы а в остальных местах нули и такая матрица не совершает преобразований
    modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(590.f, 50.f, 0.f)); // на 590 ед мы сместили по x  то есть треугольник 100 по ширине и 640-50=590 // 100 длина 480 -100 + 50(чтобы вылез)

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f); // ортографическая матрица передаем характеристики фрустона // static_cast<float>

    pSpriteShaderProgram->use();
    pTextureAtas->bind();////////////////////////////////////////////////////////////////////////
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix4("projectionMatrix", projectionMatrix);
   
    std::vector<std::string> tanksSubTexturesNames = {
    "tankTop1",
    "tankTop2",
    "tankLeft1",
    "tankLeft2",
    "tankBottom1",
    "tankBottom2",
    "tankRight1",
    "tankRight2"
    };

    auto pTanksTextureAtas = ResourceManager::loadTextureAtlas("TanksTextureAtlas", "/res/textures/tanks.png", std::move(tanksSubTexturesNames), 16, 16);
    auto pTanksAnimatedSprite = ResourceManager::loadAnimatedSprites("TanksAnimatedSprite", "TanksTextureAtlas", "SpriteShaderProgram", 100, 100, "tankTop1");
    std::vector<std::pair<std::string, uint64_t>> tankTopState;
    tankTopState.emplace_back(std::make_pair<std::string, uint64_t>("tankTop1", 500000000));
    tankTopState.emplace_back(std::make_pair<std::string, uint64_t>("tankTop2", 500000000));
    
    std::vector<std::pair<std::string, uint64_t>> tankBotoomState;
    tankBotoomState.emplace_back(std::make_pair<std::string, uint64_t>("tankBottom1", 500000000));
    tankBotoomState.emplace_back(std::make_pair<std::string, uint64_t>("tankBottom2", 500000000));

    std::vector<std::pair<std::string, uint64_t>> tankRightState;
    tankRightState.emplace_back(std::make_pair<std::string, uint64_t>("tankRight1", 500000000));
    tankRightState.emplace_back(std::make_pair<std::string, uint64_t>("tankRight2", 500000000));

    std::vector<std::pair<std::string, uint64_t>> tankLeftState;
    tankLeftState.emplace_back(std::make_pair<std::string, uint64_t>("tankLeft1", 500000000));
    tankLeftState.emplace_back(std::make_pair<std::string, uint64_t>("tankLeft2", 500000000));

    pTanksAnimatedSprite->insertState("tankTopState", std::move(tankTopState));
    pTanksAnimatedSprite->insertState("tankBottomState", std::move(tankBotoomState));
    pTanksAnimatedSprite->insertState("tankRightState", std::move(tankRightState));
    pTanksAnimatedSprite->insertState("tankLeftState", std::move(tankLeftState));

    pTanksAnimatedSprite->setState("tankTopState");
    m_pTank = std::make_unique<Tank>(pTanksAnimatedSprite, 0.0000001f, glm::vec2(100.f,100.f)); ///////////////////////////////////////////////////////
    return true;
}
