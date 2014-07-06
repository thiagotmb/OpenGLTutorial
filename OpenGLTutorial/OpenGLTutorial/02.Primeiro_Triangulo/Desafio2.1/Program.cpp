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
GLuint VAO1;
GLuint VAO2;
GLint shaderProgram;


//String com o codigo do vertex shader
const GLchar* vertexShaderSource = "#version 330 core\n" //Informa versao do shader e que é do tipo core profile
"layout (location = 0) in vec2 position;\n" //define a localizacao do atributo de entrada de vertice e declara o atributo
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, 0.0, 1.0);\n" //retorna a posicao 2D transformada para o plano 3D
"}\0";

//String com o codigo do fragment shader
const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n" //define o atributo de saida
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n" //retorna uma cor RGBA como saida de cor
"}\n\0";




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
    
    // return a window create, for use in main
    //Retorna um janela criada para ser usada no programa principal
    return window;
    
}

void Program::setupGLSL(){
//* configuracoes de buffer
    
    
    //Define vertices que serao desenhados ( triangulo)
    GLfloat verticesOne[] = {
        -0.5f, -0.5f,	   // Top Right
        -0.5f, 0.5f,   // Bottom Right
        0.5f, -0.5f,  // Bottom Left// Top Left
    };
    
    //Define vertices que serao desenhados ( triangulo)
    GLfloat verticesTwo[] = {
        0.5f, -0.5f,	   // Top Right
        0.5f, 0.5f,   // Bottom Right
        -0.5f, 0.5f,  // Bottom Left// Top Left
    };


    GLuint VBO1, VBO2;
    
    //Cria um objeto de array de vertices
    glGenVertexArrays(1,&VAO1);
    glGenVertexArrays(1,&VAO2);
    //Cria um objeto de buffer de vértices
	glGenBuffers(1, &VBO1);
    glGenBuffers(1,&VBO2);
    //Liga o array de objetos de vertice
    glBindVertexArray(VAO1);
    
    //Copia o buffer para o objeto de buffer a ser usado pelo OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    //Copia os dados de vertices definidos para o objeto de buffer, e configura como será desenhado
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesOne), verticesOne, GL_STATIC_DRAW);
    
    //Envia informacoes ao OpenGL de como será os atributos dos vertices passados ao shader
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    //Ativa os atributos configurados
    glEnableVertexAttribArray(0);
    

    //Desliga array de objetos de vertice
    glBindVertexArray(0);
    

    
    //Liga o array de objetos de vertice
    glBindVertexArray(VAO2);
    
    //Copia o buffer para o objeto de buffer a ser usado pelo OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    //Copia os dados de vertices definidos para o objeto de buffer, e configura como será desenhado
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTwo), verticesTwo, GL_STATIC_DRAW);
    
    //Envia informacoes ao OpenGL de como será os atributos dos vertices passados ao shader
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    //Ativa os atributos configurados
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);

    
//    
//    glGenBuffers(1, &EBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//    



//
    
// Configura os shaders
    
    GLint success;
    GLchar infoLog[512];
    
    //Cria um shader de vertice e guarda sua localizacao em uma variavel
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //Copia o código do shader para o shader criado
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    //Compila o shader 
    glCompileShader(vertexShader);
    //Passa a informacao sobre o estado de compilacao para uma variavel
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    //Verifica se o shader foi compilado com sucesso
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    
    //Rotina do fragment shader é similar a do Vertex Shader acima
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    //Cria um programa de shaders e liga a uma variavel
    shaderProgram = glCreateProgram();
    
    //Liga os shaders criados ao programa de shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    
    //Liga o programa de shader no OpenGL
    glLinkProgram(shaderProgram);
    
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        
        glGetProgramInfoLog(shaderProgram,512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        
    }
    
    //Deleta os shaders criados pois ja estao dentro do programa(trash)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    
//
  
}



void Program::render(){
    
    //Define a cor de limpeza do buffer
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    //Limpa o bufer com o tipo de limpeza por cor
    glClear(GL_COLOR_BUFFER_BIT);
    
    //Informa ao OpenGL que vai usar o programa de shader respsctivo para desenhar
    glUseProgram(shaderProgram);
    
    //Liga o array de objetos de vertice
    glBindVertexArray(VAO1);
    //Desenha as primitivas passadas para o VBO
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    //Desliga o array de objetos de vertice
    glBindVertexArray(0);
    glBindVertexArray(VAO2);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
   
}
