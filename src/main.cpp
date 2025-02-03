#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<string>
#include"Renderer/ShaderProgram.h" 
#include"Resources/ResourceManager.h" 
#include"Renderer/Texture2D.h" 
#include "external/glm/vec2.hpp"
#include "external/glm/mat4x4.hpp"
#include "external/glm/gtc/matrix_transform.hpp"
#include "Renderer/Sprite.h"
#include "Renderer/AnimatedSprite.h"    
#include <chrono>
#include <thread>


GLfloat point[] = { //typedef float GLfloat;
    0.0f, 50.0f, 0.0f, // передать саму программы шейдера и данные видеокарты //////////////////////
    50.0f, -50.0f, 0.0f,
   -50.0f, -50.0f, 0.0f
};

// попробовать заменить на textures
GLfloat colors[] = {
    1.0f, 0.1f, 0.0f,
    0.0f, 1.2f, 0.0f,
    0.0f, 0.1f, 1.0f
};


GLfloat textures[] = {
    0.5f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f
};



glm::vec2 g_windowSize(640, 480);

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height) {

    g_windowSize.x = width;
    g_windowSize.y = height;
    glViewport(0, 0, g_windowSize.x, g_windowSize.y); // показывает откуда и куда мы рисуем(0,0 это левый нижниый угол) 
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action/*какой ивент произошел например press*/, int mode) {

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
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

    glClearColor(0, 1, 0, 1);


    {
        ResourceManager ResourceManager(argv[0]);
        auto pShaderProgram = ResourceManager.loadShaders("DefShaderProgram", "/res/shaders/vertexShader.txt", "/res/shaders/fragmentShader.txt"); //есть ли разница передавать /res/shaders/vertexShader.txt и res/shaders/vertexShader.txt прост овсе равно потом я добавлю в открытии файла + '/'
        if (pShaderProgram == nullptr) {
            std::cerr << "Can`t create shader progam" << std::endl;
            return -1;
        }

        auto pSpriteShaderProgram = ResourceManager.loadShaders("SpriteShaderProgram", "/res/shaders/vSprite.txt", "/res/shaders/fSprite.txt"); //есть ли разница передавать /res/shaders/vertexShader.txt и res/shaders/vertexShader.txt прост овсе равно потом я добавлю в открытии файла + '/'
        if (pSpriteShaderProgram == nullptr) {

            std::cerr << "Can`t create SpriteShader progam" << std::endl;
            return -1;
        }

        auto tex = ResourceManager.loadTexture("DefaultTexture", "/res/textures/map_16x16.png");

        std::vector<std::string> subTexturesNames = {"block", 
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

        auto pTextureAtas = ResourceManager.loadTextureAtlas("DefaultTextureAtlas", "/res/textures/map_16x16.png", std::move(subTexturesNames), 16, 16);
        auto pSprite = ResourceManager.loadSprites("DefaultSprite", "DefaultTextureAtlas", "SpriteShaderProgram", 100, 100,"beton");
        pSprite->setPosition(glm::vec2(300, 100));
        auto pAnimatedSprite = ResourceManager.loadAnimatedSprites("DefaultAnimatedSprite", "DefaultTextureAtlas", "SpriteShaderProgram", 100, 100, "beton");
        pAnimatedSprite->setPosition(glm::vec2(300, 300));
        std::vector<std::pair<std::string, uint64_t>> waterState;
        waterState.emplace_back(std::make_pair<std::string , uint64_t>("water1",1000000000));///////////???????????????????????
        waterState.emplace_back(std::make_pair<std::string , uint64_t>("water2",1000000000));///////////???????????????????????
        waterState.emplace_back(std::make_pair<std::string , uint64_t>("water3",1000000000));///////////???????????????????????

        std::vector<std::pair<std::string, uint64_t>> eagleState;
        eagleState.emplace_back(std::make_pair<std::string, uint64_t>("eagle", 1000000000));///////////???????????????????????
        eagleState.emplace_back(std::make_pair<std::string, uint64_t>("deadEagle", 1000000000));///////////???????????????????????

        pAnimatedSprite->insertState("waterState", std::move(waterState));
        pAnimatedSprite->insertState("eagleState", std::move(eagleState));

        pAnimatedSprite->setState("waterState");

        //далее нам нужно передать необходимую информацию видеокарте(кординаты и цвета)
        // В контексте OpenGL буфер — это область памяти, которая используется для хранения данных. Например, буфер может хранить информацию о вершинах (вертексах), цветах, текстурах или других данных, которые могут быть использованы при рендеринге.
        //VBO — это тип буфера, который используется для хранения данных о вершинах (например, координатах, нормалях, цветах и текстурных координатах). Эти данные передаются на видеокарту, где их можно использовать в шейдерах для рендеринга объектов.
        GLuint points_vbo = 0;// хендлер хранящий идентификатор от драйвера
        glGenBuffers(1, &points_vbo);//  Когда ты вызываешь glGenBuffers, OpenGL создает новый буфер и присваивает ему уникальный ID, который ты можешь использовать для дальнейшей работы с этим буфером.
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);// //  подключили и сделали текущим(тип буфера и сам буфер)
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);//команда выполняется именно для текущего буффера с определнным параметром(GL_ARRAY_BUFFER)// передаем данные в видеокарту, позиции наши вертекса(вид буфера, размер буфера в байтах,указатель на буфер, затем даем подсказку для драйвера куда хотим записать данные на gpu для оптимального размещения данных на видеокарте, то есть если мы намереваемся часто менять буфер, то поставили мы динамис и драйвер бы разместил бы данные например там где запись данных происходит быстрее)

        GLuint colors_vbo = 0;// тоже самое как и с кордами
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
        //пока видеокарта не знает что делать с этими данными и чтобы связять их с входными атрибутами шейдера нам нужно vertex_array_obj

        GLuint texCood_vbo = 0;// тоже самое как и с кордами
        glGenBuffers(1, &texCood_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, texCood_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(textures), textures, GL_STATIC_DRAW);

        GLuint vao = 0; // id
        glGenVertexArrays(1, &vao);//(сколько эррев надо сгенить)
        glBindVertexArray(vao);

        // теперь надо связать наши vbo с позицией куда они попадут в шейдер
        glEnableVertexAttribArray(0);//функция включает 0-ую поз в шейдере
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);// делаем текущ буфер
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);// команда только для активного буфера//передаем 3 вертекса(3век по 3), формат данных,нормирование данных и какая-то хуйня с шагом если данные не попорядку и если есть смещение массива  

        //тож самое
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, texCood_vbo);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback); // callback для изменения разрешения 
        glfwSetKeyCallback(pWindow, glfwKeyCallback); // callback для escape

        glm::mat4 modelMatrix_1 = glm::mat4(1.f); // матрица в которой по диагонали единицы а в остальных местах нули и такая матрица не совершает преобразований
        modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(50.f, 50.f, 0.f));


        glm::mat4 modelMatrix_2 = glm::mat4(1.f); // матрица в которой по диагонали единицы а в остальных местах нули и такая матрица не совершает преобразований
        modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(590.f, 50.f, 0.f)); // на 590 ед мы сместили по x  то есть треугольник 100 по ширине и 640-50=590 // 100 длина 480 -100 + 50(чтобы вылез)

        glm::mat4 projectionMatrix = glm::ortho(0.f,g_windowSize.x, 0.f, g_windowSize.y, -100.f, 100.f); // ортографическая матрица передаем характеристики фрустона // static_cast<float>

        pShaderProgram->use();
        pShaderProgram->setInt("tex", 0);// после активизации шейдера мы записываем в переменную tex нашу текстуру из 0 слота
        pShaderProgram->setMatrix4("projectionMatrix", projectionMatrix);
       
        pSpriteShaderProgram->use();
        pTextureAtas->bind();////////////////////////////////////////////////////////////////////////
        pSpriteShaderProgram->setInt("tex", 0);
        pSpriteShaderProgram->setMatrix4("projectionMatrix", projectionMatrix);
        pShaderProgram->setMatrix4("modelMatrix", modelMatrix_1);

        auto lastTime = std::chrono::high_resolution_clock::now();      

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(pWindow))//если стоит флаг !true(который мы поставили в keyCallback), то выходим из цикла и завершаем работу
        {
            auto currentTime = std::chrono::high_resolution_clock::now();
            uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
            lastTime = currentTime;
            pAnimatedSprite->update(duration);

            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);
            
            //чтобы нарисовать подключаем шейдеры которые хотим использовать для рисования
            //pShaderProgram->use();
            glBindVertexArray(vao);// подключаем vao которые хотим отрисовать
            tex->bind();

            pShaderProgram->use();
            pShaderProgram->setMatrix4("modelMatrix", modelMatrix_1);
            glDrawArrays(GL_TRIANGLES, 0, 3);// вид примитива, индекс с которого рисуем и количество вертексов

            pShaderProgram->setMatrix4("modelMatrix", modelMatrix_2);
            glDrawArrays(GL_TRIANGLES, 0, 3);//
            
            pSprite->Render();
            pAnimatedSprite->Render();

            /* Swap front and back buffers */
            glfwSwapBuffers(pWindow);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}