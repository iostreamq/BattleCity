#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<string>
#include "external/glm/vec2.hpp"
#include "external/glm/mat4x4.hpp"
#include "external/glm/gtc/matrix_transform.hpp"
#include "Resources/ResourceManager.h"
#include <chrono>
#include <thread>
#include "Game/Game.h"
#include "Renderer/Renderer.h"


glm::ivec2 g_windowSize(13*16, 14*16);
Game g_game(g_windowSize);

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height) {

    g_windowSize.x = width;
    g_windowSize.y = height;

    const float map_aspect_ratio = 13.f / 14.f;
    unsigned int viewPortWidth = width;
    unsigned int viewPortHeight = height; 
    unsigned int viewPortLeftOffset = 0;
    unsigned int viewPortBottomOffset = 0;

    if (static_cast<float>(g_windowSize.x / g_windowSize.y) > map_aspect_ratio) // делаем ширину под высоту 
    {
        viewPortWidth = g_windowSize.y * map_aspect_ratio;
        viewPortLeftOffset = (g_windowSize.x - viewPortWidth) / 2;
    }
    else
    {
        viewPortHeight = g_windowSize.x / map_aspect_ratio;
        viewPortLeftOffset = (g_windowSize.y - viewPortHeight) / 2;
    }

    RenderEngine::Renderer::setViewport(viewPortLeftOffset, viewPortBottomOffset, viewPortWidth, viewPortHeight); // показывает откуда и куда мы рисуем(0,0 это левый нижниый угол) 
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action/*какой ивент произошел например press*/, int mode) {

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
    g_game.setKey(key, action); /////////////////////////////////
}

int main(int argc, char** argv)
{
  
  

    /* Initialize the library */
    if (!glfwInit()) {

        std::cout << "glfwInit failed!" << std::endl;
        return -1;
    }

    //min version for OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//множество функций в которые не включены функции для обратной совместимости(различные версии OpenGL), которые нам и не нужны
    /* Create a windowed mode window and its OpenGL context */

    GLFWwindow* pWindow = glfwCreateWindow(g_windowSize.x, g_windowSize.y, "Battle City", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "glfwCreateWindow failed!" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL())
    {
        std::cout << "Can`t load GLAD" << std::endl;
        return -1;
    }

    std::cout << "Renderer: " << RenderEngine::Renderer::getRendererStr() << std::endl;
    std::cout << "OpenGL version: " <<RenderEngine::Renderer::getVersionStr() << std::endl;

    RenderEngine::Renderer::setCleatColor(0, 0, 0, 0);

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback); // callback для изменения разрешения 
    glfwSetKeyCallback(pWindow, glfwKeyCallback); // callback для escape

    {
     
        auto lastTime = std::chrono::high_resolution_clock::now();
        // только после создания контекста и инициализации openGL
        ResourceManager::setExecutablePath(argv[0]);
        g_game.init();
        
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(pWindow))//если стоит флаг !true(который мы поставили в keyCallback), то выходим из цикла и завершаем работу
        {
            auto currentTime = std::chrono::high_resolution_clock::now();
            uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
            lastTime = currentTime;
            g_game.update(duration);
           
             /* Render here */
            RenderEngine::Renderer::clear();
           
           g_game.Render();
            /* Swap front and back buffers */
            glfwSwapBuffers(pWindow);

            /* Poll for and process events */
            glfwPollEvents();
        }
        ResourceManager::unloadAllResources();
    }
    glfwTerminate();
    return 0;
}