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
#include <GL/glew.h>
#include <GL/glfw3.h>

class Program{
    
public:
    Program();
    ~Program();
    
    
    GLFWwindow* initOpenGL();
    
private:
    
    
};

#endif /* defined(__OpenGLTutorial__Program__) */
