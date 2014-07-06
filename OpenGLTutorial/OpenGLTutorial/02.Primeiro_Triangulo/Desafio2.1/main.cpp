//
//  main.cpp
//  OpenGLTutorial
//
//  Created by Thiago Bernardes on 7/3/14.
//  Copyright (c) 2014 TMB. All rights reserved.
//

#include <iostream>
#include "Program.h"

GLFWwindow* mainWindow;




int main(int argc, const char * argv[])
{

    Program firstProgram = Program();
    
    //Window recebe a nossa janela criada pela função que vimos anteriormente.
    mainWindow = firstProgram.initOpenGL();
    
    //Configura os shaders e ligacoes com OpenGL
    firstProgram.setupGLSL();
    
    //Verifica se a janela criada foi fechada a cada iteração.
    while(!glfwWindowShouldClose(mainWindow)){
        
        //Verifica todos os eventos e chama as funções relacionadas a esses eventos
        glfwPollEvents();
        
        firstProgram.render();
        
        //Troca o buffer de cor a cada iteração pelo definido.
        glfwSwapBuffers(mainWindow);
    }
    
    glfwTerminate();
    
    std::cout << "Hello, World!\n";
    return 0;
}

