#include "Context.h"

#include<iostream>

unsigned int g_X;
unsigned int g_Y;

Context::Context(){

    
}

Context::Context(const Config &config)
{
    std::cout<<"ContextSetupDebug1"<<std::endl;
    primary = glfwGetPrimaryMonitor();
    std::cout<<"ContextSetupDebug2"<<std::endl;
    assert(glfwInit());
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES,4);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    std::cout<<"ContextSetupDebug3"<<std::endl;
    theWindow = glfwCreateWindow(config.windowX, config.windowY, "StuffCraft", NULL, NULL);
    std::cout<<"ContextSetupDebug4"<<std::endl;
    glfwGetFramebufferSize(theWindow, &framebufferWidth, &framebufferHeight);
    glfwSetFramebufferSizeCallback(theWindow, frameBufferRez);
    std::cout<<"ContextSetupDebug5"<<std::endl;
    glfwMakeContextCurrent(theWindow); //Important!!!!

    //GLAD check
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    std::cout<<"ContextSetupDebug6"<<std::endl;
    glfwSetInputMode(theWindow, GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    //glfwSetCursorPosCallback(windax, mouseInput);
    glfwSetScrollCallback(theWindow, scrollInput);
    std::cout<<"ContextSetupDebug7"<<std::endl;
    glfwSetErrorCallback(glfw_onError);
    glViewport(0, 0, config.windowX, config.windowY);

    glCullFace(GL_BACK);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    std::cout<<"ContextSetupDebug8"<<std::endl;
}
