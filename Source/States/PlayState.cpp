#include "PlayState.h"

#include "../Application.h"
#include "../Maths/Ray.h"
#include "../Renderer/RenderMaster.h"
#include "../World/Event/PlayerDigEvent.h"

#include <iostream>

StatePlay::StatePlay(Application &app, const Config &config)
    : StateBase(app)
    , m_world(app.getWindow(), app.getCamera(), config, m_player)
{
    app.getCamera().hookEntity(m_player);

    m_player.setWindow(app.getWindow());

}

void StatePlay::handleEvent(int e)
{
    //m_keyboard.update(e);
}

void StatePlay::handleInput(GLFWwindow* window)
{
    m_player.handleInput();

    double previousTime = glfwGetTime();
    glm::vec3 lastPosition;

    // Ray is cast as player's 'vision'
    for (Ray ray({m_player.position.x, m_player.position.y + 0.6f,
                  m_player.position.z},
                 m_player.rotation); // Corrected for camera offset
         ray.getLength() < 6; ray.step(0.05f)) {
        int x = static_cast<int>(ray.getEnd().x);
        int y = static_cast<int>(ray.getEnd().y);
        int z = static_cast<int>(ray.getEnd().z);

        auto block = m_world.getBlock(x, y, z);
        auto id = (BlockId)block.id;

        if (id != BlockId::Air && id != BlockId::Water) {
            if (glfwGetTime() - previousTime > 0.2) {
                if(glfwGetKey(window, GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS) {
                    previousTime = glfwGetTime();
                    // The player "digs" the block up
                    m_world.addEvent<PlayerDigEvent>(GLFW_MOUSE_BUTTON_LEFT,
                                                     ray.getEnd(), m_player);
                    break;
                }
                else if(glfwGetKey(window, GLFW_MOUSE_BUTTON_RIGHT)==GLFW_PRESS) {
                    previousTime = glfwGetTime();
                    // Block is placed by player
                    m_world.addEvent<PlayerDigEvent>(GLFW_MOUSE_BUTTON_RIGHT,
                                                     lastPosition, m_player);
                    break;
                }
            }
        }
        lastPosition = ray.getEnd();
    }
}

void StatePlay::update(float deltaTime)
{
    if (m_player.position.x < 0)
        m_player.position.x = 0;
    if (m_player.position.z < 0)
        m_player.position.z = 0;

    m_fpsCounter.update();
    m_player.update(deltaTime, m_world);
    m_world.update(m_pApplication->getCamera());
}

void StatePlay::render(RenderMaster &renderer)
{

    static bool drawGUI = false;

    if(glfwGetKey(renderer.getWindow(), GLFW_KEY_F3)==GLFW_PRESS) {
        drawGUI = !drawGUI;
    }

    if (drawGUI) {
        m_fpsCounter.draw(renderer);
    }

    m_world.renderWorld(renderer, m_pApplication->getCamera());
}

void StatePlay::onOpen()
{
    m_pApplication->turnOffMouse();
}
