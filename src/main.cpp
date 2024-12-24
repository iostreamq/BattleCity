#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>

int g_windowSizeX = 640;
int g_windowSizeY = 480;

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height) {

    g_windowSizeX = width;
    g_windowSizeY = height;
    glViewport(0, 0, g_windowSizeX, g_windowSizeY); // показывает откуда и куда мы рисуем(0,0 это левый нижниый угол) 
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action/*какой ивент произошел например press*/, int mode) {

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(pWindow,GL_TRUE);
    }
}

int main(void)
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

    GLFWwindow* pWindow = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "Battle City", nullptr, nullptr);
    if (!pWindow)
    {
       std::cout<<"glfwCreateWindow failed!"<<std::endl;
       glfwTerminate();
       return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);
	
	if(!gladLoadGL())
	{		
	std::cout<<"Can`t load GLAD"<<std::endl;
	return -1;
	}

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	glClearColor(0,1,0,1);

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback); // callback для изменения разрешения 
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))//если стоит флаг что окно должно быть закрыто, то выходим из цикла и завершаем работу
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}