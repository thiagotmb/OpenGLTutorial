//
//  Shader.cpp
//  OpenGLTutorial
//
//  Created by Thiago Bernardes on 7/6/14.
//  Copyright (c) 2014 TMB. All rights reserved.
//

#include "Shader.h"

Shader::Shader(){};

Shader::~Shader(){};

void Shader::initShader(const char* vertexPath, const char* fragmentPath){
    
    // Irá guarda o código do shader de um arquivo
    std::string vertexShaderSource;
    std::string fragmentShaderSource;
    try
    {
        // Abre os arquivos
        std::ifstream vShaderFile(vertexPath);
        //verifica se foi aberto
        if(!vShaderFile.is_open()){
            throw std::runtime_error("");
        }
        
        
        std::ifstream fShaderFile(fragmentPath);
        
        if(!fShaderFile.is_open()){
            throw std::runtime_error("");
        }
        
        std::stringstream vShaderStream, fShaderStream;
        
        // Le o conteudo do arquivo e salva nas variáveis string
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        
        
        // fecha o arquivo
        vShaderFile.close();
        fShaderFile.close();
        
        // Converte a strint para o tipo const char, para ser lido pelo shader.
        vertexShaderSource = vShaderStream.str();
        fragmentShaderSource = fShaderStream.str();
        
    }
    catch(std::exception e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
   
    //guarda a string em uma array de chars do OpenGL
    const GLchar* vertexShaderCode = vertexShaderSource.c_str();
    const GLchar* fragmentShaderCode = fragmentShaderSource.c_str();
    
    // Configura os shaders
    GLint success;
    GLchar infoLog[512];
    
    //Cria um shader de vertice e guarda sua localizacao em uma variavel
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //Copia o código do shader para o shader criado
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
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
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    
    //Cria um programa de shaders e liga a uma variavel
    this->shaderProgram = glCreateProgram();
    //Liga os shaders criados ao programa de shaders
    glAttachShader(this->shaderProgram, vertexShader);
    glAttachShader(this->shaderProgram, fragmentShader);
    //Liga o programa de shader no OpenGL
    glLinkProgram(this->shaderProgram);
    glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        
        glGetProgramInfoLog(this->shaderProgram,512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        
    }
    
    //Deleta os shaders criados pois ja estao dentro do programa(trash)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    //
}

void Shader::use(){
    
    //Configura o opengl para usar esse programa de shaders.
    glUseProgram(this->shaderProgram);
    
}