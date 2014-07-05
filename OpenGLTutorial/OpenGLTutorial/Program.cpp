//
//  Program.cpp
//  OpenGLTutorial
//
//  Created by Thiago Bernardes on 7/3/14.
//  Copyright (c) 2014 TMB. All rights reserved.
//


#include "Program.h"

#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 600

GLFWwindow* window;

Program::Program(){};

Program::~Program(){};

// Is called whenever a key is pressed/released via GLFW
// É chamado sempre que uma tecla é pressionada ou solta , através do GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    std::cout << key << std::endl;
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

}

//Inicialisa o GLFW, o GLEW e cria um contexto de OpenGL
GLFWwindow* Program::initOpenGL(){
    
    //initi GLFW
    //Inicializa o GLEW
    if (!glfwInit())
        exit(EXIT_FAILURE);
    
    //Force glfw to use the opengl version 3.3
    //Força o GLFW a usar a versao 3.3 do OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //create a window in a system
    //Cria uma janela no sistema
    window = glfwCreateWindow(SCREEN_SIZE_X, SCREEN_SIZE_Y,"OpenGL Tutorial", NULL, NULL);
    
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    // create a opengl context in this window, always before the initialize opengl in  glew, because for glew initialize, it should have a context  for init.
    //Cria um contexto OpenGL em uma janela, sempre antes de inicialiar o OpenGL pelo glew, deve se existir um contexto, para o glew ser criado dentro do mesmo
    glfwMakeContextCurrent(window);
    
    
    glViewport(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y);

    
    //Initialize glew
    //Inicializa o GLEW
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");
    
    //Check API 3.2 is avaible
    //Checa se o OpenGL 3.2 existe
    if(!GLEW_VERSION_3_2)
        throw std::runtime_error("OpenGL 3.2 API is not available.");
    
    // print out some info about the graphics drivers
    // Imprime no console as informacoes sobre as extensões gráficas do contexto criado
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    
    //Define qual funcao de KeyCallBack será chamada e para qual janela ela irá funcionar.
    glfwSetKeyCallback(window, key_callback);
    
    // return a window create, for use in main
    //Retorna um janela criada para ser usada no programa principal
    return window;
    
}


