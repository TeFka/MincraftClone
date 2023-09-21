#pragma once

#include<windows.h>
#include<cassert>

#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>
#include <glad/glad.h>

#include "Config.h"

/// @brief Struct related to window and application context.
struct Context {
    Context();
    Context(const Config &config);

    GLFWwindow* theWindow;
    GLFWmonitor* primary;

    int framebufferWidth;
    int framebufferHeight;

    static void frameBufferRez(GLFWwindow *window, int fbW, int fbH)
    {
        glViewport(0,0, fbW, fbH);
    }

    static void scrollInput(GLFWwindow* window, double xSet, double ySet)
    {
        //mainCamera.scrollCall(ySet);
    }

    static void glfw_onError(int error, const char* description)
    {
        // print message in Windows popup dialog box
        MessageBoxA(NULL, description, "GLFW error", MB_OK);

    }
    
};
