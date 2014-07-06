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
GLuint VAO;
Shader newShader;
float xOffsetValue;


Program::Program(){};

Program::~Program(){};

// Is called whenever a key is pressed/released via GLFW
// É chamado sempre que uma tecla é pressionada ou solta , através do GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    std::cout << key << std::endl;
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    
    if(key == GLFW_KEY_W && action == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    if(key == GLFW_KEY_S && action == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
        xOffsetValue+=0.05;
    
    if(key == GLFW_KEY_LEFT && action == GLFW_PRESS)
        xOffsetValue-=0.05;

    
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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
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
    
    xOffsetValue = 0;

    
    // return a window create, for use in main
    //Retorna um janela criada para ser usada no programa principal
    return window;
    
}

void Program::setupGLSL(){
//* configuracoes de buffer
    
    
    //Define vertices que serao desenhados
    GLfloat vertices[] = {
        // Posicoes 	// Cores
        0.5f, 0.5f,     1.0f, 0.0f, 0.0f, //vermelho
        0.5f, -0.5f,	0.0f, 1.0f, 0.0f, //verde
       -0.5f, -0.5f,    0.0f, 0.0f, 1.0f, //azul
        -0.5, 0.5,      1.0f, 1.0f, 1.0f //branco
    };

    
    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    
    
    //Cria um objeto de array de vertices
    glGenVertexArrays(1,&VAO);
    //Liga o array de objetos de vertice
    glBindVertexArray(VAO);
    
    GLuint VBO, EBO;
    
    //Cria um objeto de buffer de vértices
	glGenBuffers(1, &VBO);
    //Copia o buffer para o objeto de buffer a ser usado pelo OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Copia os dados de vertices definidos para o objeto de buffer, e configura como será desenhado
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    
    //Envia informacoes ao OpenGL de como será os atributos dos vertices passados ao shader
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
                          5 * sizeof(GLfloat), (GLvoid*)0);
    //Ativa os atributos configuradoz
    glEnableVertexAttribArray(0);
    //Similar ao acima, mas relacionado a cor
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                          5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    //Desliga array de objetos de vertice
    glBindVertexArray(0);

//
    const char* vertexPath = "/Users/thiagoTMB/Documents/Repositories/Tutorials/OpenGLTutorial/OpenGLTutorial/OpenGLTutorial/vertex.glsl";
    const char* fragmentPath = "/Users/thiagoTMB/Documents/Repositories/Tutorials/OpenGLTutorial/OpenGLTutorial/OpenGLTutorial/fragment.glsl";
    newShader = Shader();
    newShader.initShader(vertexPath, fragmentPath);
    

}



void Program::render(){
    
    //Define a cor de limpeza do buffer
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    //Limpa o bufer com o tipo de limpeza por cor
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    GLint xOffsetLocation = glGetUniformLocation(newShader.shaderProgram, "xOffset");
    glUniform1f(xOffsetLocation,xOffsetValue);
    
    
    //Informa ao OpenGL que vai usar o programa de shader respsctivo para desenhar
    newShader.use();
    
    //Liga o array de objetos de vertice
    glBindVertexArray(VAO);
    //Desenha as primitivas passadas para o VBO
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    //Desliga o array de objetos de vertice
    glBindVertexArray(0);
   
}



