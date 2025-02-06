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


glm::ivec2 g_windowSize(640, 480);
Game g_game(g_windowSize);

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height) {

    g_windowSize.x = width;
    g_windowSize.y = height;
    glViewport(0, 0, g_windowSize.x, g_windowSize.y); // показывает откуда и куда мы рисуем(0,0 это левый нижниый угол) 
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

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glClearColor(0, 0, 0, 1);

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback); // callback для изменения разрешения 
    glfwSetKeyCallback(pWindow, glfwKeyCallback); // callback для escape

    {
     
       
        auto lastTime = std::chrono::high_resolution_clock::now();
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
           glClear(GL_COLOR_BUFFER_BIT);
           
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