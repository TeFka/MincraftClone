#include "Application.h"
#include "States/PlayState.h"
#include "World/Block/BlockDatabase.h"
#include <iostream>

Application::Application(){



}

Application::Application(const Config &config)
    : m_context(config)
    , m_camera(config)
    , m_config(config)
{
    std::cout<<"AppSetupDebug1"<<std::endl;
    m_masterRenderer.setWindow(m_context.theWindow);
    std::cout<<"AppSetupDebug2"<<std::endl;
    BlockDatabase::get();
    std::cout<<"AppSetupDebug3"<<std::endl;
    pushState<StatePlay>(*this, config);
    std::cout<<"AppSetupDebug4"<<std::endl;
}

float g_timeElapsed = 0;

/// @brief Game loop utilizing a mixture of SFML events and GL rendering.
void Application::runLoop()
{
    double timerTime = glfwGetTime();
    double dTime = glfwGetTime();
    glm::ivec2 win_center;
    //std::cout<<"Debug1"<<std::endl;
    double m;

    // Grab the context window and force it to a certain position.
    // This prevents the window from sticking to the bottom of the visible screen like it does
    // in some Linux distros. Especially Arch.

    // If the window is small, use these parameters

    int width, height;
    glfwGetWindowSize(m_context.theWindow, &width, &height);
    //std::cout<<"Debug2"<<std::endl;
    if(width <= 640)
    {
        int width_mm, height_mm;
        glfwGetMonitorPhysicalSize(m_context.primary, &width_mm, &height_mm);
        win_center = {
            width_mm / 3.5,
            height_mm / 4
        };
    }
    else // Else force it to the upper-leftgit p
    {
        win_center = { 0,0 };
    }
    //std::cout<<"Debug3"<<std::endl;
    glfwSetWindowMonitor(m_context.theWindow, m_context.primary, win_center.x, win_center.y, width, height, GLFW_DONT_CARE);
    //std::cout<<"Debug4"<<std::endl;
    while (!m_states.empty()) {
        auto deltaTime = glfwGetTime() - timerTime;
        auto &state = *m_states.back();
        //std::cout<<"Debug5"<<std::endl;
        state.handleInput(m_context.theWindow);
        state.update(deltaTime);
        m_camera.update();
        //std::cout<<"Debug6"<<std::endl;
        state.render(m_masterRenderer);
        m_masterRenderer.finishRender(m_context.theWindow, m_camera);
        //std::cout<<"Debug7"<<std::endl;
        //handleEvents();
        if (m_isPopState) {
            m_isPopState = false;
            m_states.pop_back();
        }
        //std::cout<<"Debug8"<<std::endl;
        m = dTime - glfwGetTime();

        g_timeElapsed += m;
    }
}

/// @brief Handles window events, especially window polling and keyboard inputs.
void Application::handleEvents()
{
    /*while (m_context.theWindow->pollEvent(e)) {
        m_states.back()->handleEvent(e);*/

    if(glfwGetKey(m_context.theWindow, GLFW_KEY_ESCAPE)==GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_context.theWindow, true);
        glfwDestroyWindow(m_context.theWindow);
    }

    //}
}

/// @brief Tell the program stack to pop off the state.
void Application::popState()
{
    m_isPopState = true;
}

/// @brief Makes the mouse invisible, doesn't actually turn off the mouse.
void Application::turnOffMouse()
{
    glfwSetInputMode(m_context.theWindow, GLFW_CURSOR,GLFW_CURSOR_DISABLED);
}

/// @brief Makes the mouse visible again.
void Application::turnOnMouse()
{
    glfwSetInputMode(m_context.theWindow, GLFW_CURSOR,GLFW_CURSOR_NORMAL);
}
