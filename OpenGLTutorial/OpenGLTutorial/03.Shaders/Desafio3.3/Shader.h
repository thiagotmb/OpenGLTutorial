//
//  Shader.h
//  OpenGLTutorial
//
//  Created by Thiago Bernardes on 7/6/14.
//  Copyright (c) 2014 TMB. All rights reserved.
//

#ifndef __OpenGLTutorial__Shader__
#define __OpenGLTutorial__Shader__

#pragma once

#include <iostream> //Fluxo de entrada e saída padrao do sistema
#include <fstream> //Manipulador de fluxo arquivos
#include <sstream> //Manipulador de fluxo strings
#include <string> //Suporte a funcoes especiais de string
#include <GL/glew.h>

class Shader{
    
public:
    Shader();
    ~Shader();
    
    //Inicializa o shader que foi passado, e cria um associa ao programa da classe
    void initShader(const char* vertexPath, const char* fragmentPath);
    
    //Programa de shader da classe
    GLuint shaderProgram;
    
    //Usa o programa de shader da classe
    void use();
private:
    
    
};

#endif /* defined(__OpenGLTutorial__Shader__) */
