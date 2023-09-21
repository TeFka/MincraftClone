#include "FPSCounter.h"

#include "../Renderer/RenderMaster.h"

#include <iostream>

FPSCounter::FPSCounter()
{
    enabled = true;
    debugging = false;

    // m_text.setPosition(sf::Vector2f(10.f,10.f));
    m_text.setPosition(glm::vec2(0.1, 0.1));
    m_text.setColor(glm::vec4(0.0));

    m_text.setTextFont("../Res/Fonts/rs.ttf");
    m_text.setScale(20);

    previousTime = glfwGetTime();
}

void FPSCounter::update()
{
    m_frameCount++;

    if(enabled)
    {
        double deltaTime = glfwGetTime()-previousTime;
        if (deltaTime > 0.5)
        {
            m_fps = m_frameCount / deltaTime;
            m_frameCount = 0;
            previousTime = glfwGetTime();
        
            // Only show this output in debug mode
            if(debugging)
            {
                std::cout << m_fps << '\n';
            }
        }
    }
}

void FPSCounter::draw(RenderMaster &renderer)
{
    m_text.setTextValue("FPS: " + std::to_string(m_fps));
    renderer.addText(&m_text);
}
