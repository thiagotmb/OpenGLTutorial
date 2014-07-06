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

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <GL/glew.h>

class Shader{
    
public:
    Shader();
    ~Shader();
    
    void initShader(const char* vertexPath, const char* fragmentPath);
    GLuint shaderProgram;
    void use();
private:
    
    
};

#endif /* defined(__OpenGLTutorial__Shader__) */
