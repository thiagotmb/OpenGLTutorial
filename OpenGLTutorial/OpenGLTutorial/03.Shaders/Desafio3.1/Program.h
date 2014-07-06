//
//  Program.h
//  OpenGLTutorial
//
//  Created by Thiago Bernardes on 7/3/14.
//  Copyright (c) 2014 TMB. All rights reserved.
//

#ifndef __OpenGLTutorial__Program__
#define __OpenGLTutorial__Program__

#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include <GL/glew.h>
#include <GL/glfw3.h>
#include "Shader.h"

class Program{
    
public:
    Program();
    ~Program();
    
    
    GLFWwindow* initOpenGL();
    void setupGLSL();
    void render();
    
private:
    
    
};

#endif /* defined(__OpenGLTutorial__Program__) */
