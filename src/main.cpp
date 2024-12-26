#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>



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

//вызываться  эти 2 шейдера будут столько раз сколько точек в пространстве(vertex) и сколько пикселей(fragment)
const char* vertex_shader =
"#version 460\n" // версия OpenGL 4.6
"layout(location = 0) in vec3 vertex_position;"//Через layout(location = X) вы привязываете данные к нужным переменным в шейдере.
"layout(location = 1) in vec3 vertex_color;" // вертекс из 3 значений со своими кординат.(xyz(всего 3))  обознач. vec3, in-входной параметр
"out vec3 color;" // на выход у нас пойдет переменная цвет,в виду rgb 1 значения по 3 параметра
"void main() {"
"color = vertex_color;" // и потом фрагмент шейдер получит интерполированное значение для каждого пикселя между вертаксами  из перменной color
"gl_Position = vec4(vertex_position, 1.0);" // позиция вертекса которая потом пойдет на выход в норм корд. Тип gl_pos 4-ых компонентный поэтому приводим(1.0 это перспектива)
"}";

const char* fragment_shader =
"#version 460\n"
"in vec3 color;"// vec3 интерполированное значение, которое мы получили от верт шейд(пишем такое же название как и в вертекс шейд.) 
"out vec4 frag_color;"
"void main() {"
"frag_color = vec4(color,1.0);" // преобразование по такому же случаю
"}";
// после написания 2-ух шейдеров нам нужно их скомпилировать и передать видеокарте 

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

    //обозначаем идентификатор(1) и приравниваем к функции которая создает шейдер(2)
    /*typedef unsigned int GLuint;*/ 
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);//1
    glShaderSource(vs, 1, &vertex_shader, nullptr);//2,передаем исходный код(vertex_shader), id, количество строк, ссылка на массив строк, и длина строк(nullptr тк нет массива строк, то есть обозначает что на вход идет массив с одной строкой и 0-ым терминальным символом)
    glCompileShader(vs);//компилирование кода шейдера(id shader`a)

    //все то же самое только fragment_shader
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, nullptr);
    glCompileShader(fs);

    
    //после компиляции нам нужно слинковать шейдеры,то есть объединить в одну шейдерную программу. при линкове идет объединение выходных значений вертех шейд с вход знач фрагмент шейд.,
    //так что, если имена и тип не совпадают - произойдет ошибка линковки.
    GLuint shader_program = glCreateProgram(); // также возвращает id
    glAttachShader(shader_program, vs);//аттачим вертексный — функция, которая привязывает шейдер к объекту программы.
    glAttachShader(shader_program, fs);// аттачим фрагмент — функция, которая привязывает шейдер к объекту программы.
    glLinkProgram(shader_program);// линковка в одну shared_program
      
    //удаляем объекты вертекс и фрагмен шейдеры 
    glDeleteShader(vs);
    glDeleteShader(fs);

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0,nullptr);// команда только для активного буфера//передаем 3 вертекса(3век по 3), формат данных,нормирование данных и какая-то хуйня с шагом если данные не попорядку и если есть смещение массива  
   
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
        glUseProgram(shader_program);
        glBindVertexArray(vao);// подключаем vao которые хотим отрисовать
        glDrawArrays(GL_TRIANGLES,0,3);// вид примитива, индекс с которого рисуем и количество вертексов

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}