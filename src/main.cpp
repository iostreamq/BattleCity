#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<string>
#include"Renderer/ShaderProgram.h" 
#include"Resources/ResourceManager.h" 



GLfloat point[] = { //typedef float GLfloat;
    0.0f, 0.5f, 0.0f, // передать саму программы шейдера и данные видеокарты
    0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f
};

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};


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

  
    {
        ResourceManager ResourceManager(argv[0]);
        auto pShaderProgram = ResourceManager.loadShaders("DefShaderProgram", "/res/shaders/vertexShader.txt", "/res/shaders/fragmentShader.txt"); //есть ли разница передавать /res/shaders/vertexShader.txt и res/shaders/vertexShader.txt прост овсе равно потом я добавлю в открытии файла + '/'
        if (pShaderProgram == nullptr) {
            std::cerr << "Can`t create shader progam" << std::endl;
            return -1;
        }
        
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

        glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback); // callback для изменения разрешения 
        glfwSetKeyCallback(pWindow, glfwKeyCallback); // callback для escape

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(pWindow))//если стоит флаг !true(который мы поставили в keyCallback), то выходим из цикла и завершаем работу
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            //чтобы нарисовать подключаем шейдеры которые хотим использовать для рисования
            pShaderProgram->use();
            glBindVertexArray(vao);// подключаем vao которые хотим отрисовать
            glDrawArrays(GL_TRIANGLES, 0, 3);// вид примитива, индекс с которого рисуем и количество вертексов

            /* Swap front and back buffers */
            glfwSwapBuffers(pWindow);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}