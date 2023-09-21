#include "Player.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "../Renderer/RenderMaster.h"
#include "../World/World.h"

Player::Player()
    : Entity({2500, 125, 2500}, {0.f, 0.f, 0.f}, {0.3f, 1.f, 0.3f})
    , m_acceleration(glm::vec3(0.f))

{   

    for (int i = 0; i < 5; i++) {
        m_items.emplace_back(Material::NOTHING, 0);
    }

    for (float i = 0; i < 5; i++) {
        Text* t = new Text("***");
        t->setTextFont("../Res/Fonts/rs.ttf");
        t->setColor(glm::vec4(0.0,0.0,0.0,1.0));
        t->setScale(25);
        t->setPosition(glm::vec2(0.1, 0.1 * i + 0.2));
        m_itemText.push_back(t);
    }
    m_posPrint.setTextFont("../Res/Fonts/rs.ttf");
    m_posPrint.setColor(glm::vec4(0.0,0.0,0.0,1.0));
    m_posPrint.setScale(25);
    m_posPrint.setPosition(glm::vec2(0.1, 0.1 * 6 + 0.2));

}

void Player::addItem(const Material &material)
{
    Material::ID id = material.id;

    for (unsigned i = 0; i < m_items.size(); i++) {
        if (m_items[i].getMaterial().id == id) {
            /*int leftOver =*/m_items[i].add(1);

            return;
        }
        else if (m_items[i].getMaterial().id == Material::ID::Nothing) {
            m_items[i] = {material, 1};
            return;
        }
    }
}

ItemStack &Player::getHeldItems()
{
    return m_items[m_heldItem];
}

void Player::handleInput()
{
    keyboardInput();
    mouseInput();

    if(glfwGetKey(theWindow, GLFW_KEY_DOWN)==GLFW_PRESS) {
        m_heldItem++;
        if (m_heldItem == (int)m_items.size()) {
            m_heldItem = 0;
        }
    }
    else if(glfwGetKey(theWindow, GLFW_KEY_UP)==GLFW_PRESS) {
        m_heldItem--;
        if (m_heldItem == -1) {
            m_heldItem = m_items.size() - 1;
        }
    }

    if(glfwGetKey(theWindow, GLFW_KEY_F)==GLFW_PRESS) {
        m_isFlying = !m_isFlying;
    }

    if(glfwGetKey(theWindow, GLFW_KEY_1)==GLFW_PRESS) {
        m_heldItem = 0;
    }
    if(glfwGetKey(theWindow, GLFW_KEY_2)==GLFW_PRESS) {
        m_heldItem = 1;
    }
    if(glfwGetKey(theWindow, GLFW_KEY_3)==GLFW_PRESS) {
        m_heldItem = 2;
    }
    if(glfwGetKey(theWindow, GLFW_KEY_4)==GLFW_PRESS) {
        m_heldItem = 3;
    }
    if(glfwGetKey(theWindow, GLFW_KEY_5)==GLFW_PRESS) {
        m_heldItem = 4;
    }
    if(glfwGetKey(theWindow, GLFW_KEY_LEFT_SHIFT)==GLFW_PRESS)
    {
        m_isSneak = !m_isSneak;
    }
}

void Player::update(float dt, World &world)
{
    std::cout<<"Player update"<<std::endl;
    velocity += m_acceleration;
    m_acceleration = {0, 0, 0};

    if (!m_isFlying) {
        if (!m_isOnGround) {
            std::cout<<"Gravity effefct"<<std::endl;
            velocity.y -= dt;
        }
        m_isOnGround = false;
    }

    if (position.y <= 0 && !m_isFlying) {
        position.y = 300;
    }

    std::cout<<"Velocity: "<<velocity.x<<" "<<velocity.y<<" "<<velocity.z<<std::endl;
    std::cout<<"Position: "<<position.x<<" "<<position.y<<" "<<position.z<<std::endl;
    position.x += velocity.x * dt;
    collide(world, {velocity.x, 0, 0}, dt);

    position.y += velocity.y * dt;
    collide(world, {0, velocity.y, 0}, dt);

    position.z += velocity.z * dt;
    collide(world, {0, 0, velocity.z}, dt);

    box.update(position);
    velocity.x *= 0.95f;
    velocity.z *= 0.95f;
    
    if (m_isFlying) {
        velocity.y *= 0.95f;
    }
}

void Player::collide(World &world, const glm::vec3 &vel, float dt)
{
    for (int x = position.x - box.dimensions.x;
         x < position.x + box.dimensions.x; x++)
        for (int y = position.y - box.dimensions.y; y < position.y + 0.7; y++)
            for (int z = position.z - box.dimensions.z;
                 z < position.z + box.dimensions.z; z++) {
                auto block = world.getBlock(x, y, z);

                if (block != 0 && block.getData().isCollidable) {
                    if (vel.y > 0) {
                        position.y = y - box.dimensions.y;
                        velocity.y = 0;
                    }
                    else if (vel.y < 0) {
                        m_isOnGround = true;
                        position.y = y + box.dimensions.y + 1;
                        velocity.y = 0;
                    }

                    if (vel.x > 0) {
                        position.x = x - box.dimensions.x;
                    }
                    else if (vel.x < 0) {
                        position.x = x + box.dimensions.x + 1;
                    }

                    if (vel.z > 0) {
                        position.z = z - box.dimensions.z;
                    }
                    else if (vel.z < 0) {
                        position.z = z + box.dimensions.z + 1;
                    }
                }
            }
}

///@TODO Move this
float speed = 0.2f;

void Player::keyboardInput()
{
    if(glfwGetKey(theWindow, GLFW_KEY_W)==GLFW_PRESS) {
        float s = speed;

        if(glfwGetKey(theWindow, GLFW_KEY_LEFT_CONTROL)==GLFW_PRESS)
            s *= 5;
        else if(glfwGetKey(theWindow, GLFW_KEY_RIGHT_SHIFT)==GLFW_PRESS || glfwGetKey(theWindow, GLFW_KEY_LEFT_SHIFT)==GLFW_PRESS)
            s *= 0.35;

        m_acceleration.x += -glm::cos(glm::radians(rotation.y + 90)) * s;
        m_acceleration.z += -glm::sin(glm::radians(rotation.y + 90)) * s;
    }
    if(glfwGetKey(theWindow, GLFW_KEY_S)==GLFW_PRESS) {
        m_acceleration.x += glm::cos(glm::radians(rotation.y + 90)) * speed;
        m_acceleration.z += glm::sin(glm::radians(rotation.y + 90)) * speed;
    }
    if(glfwGetKey(theWindow, GLFW_KEY_A)==GLFW_PRESS) {
        m_acceleration.x += -glm::cos(glm::radians(rotation.y)) * speed;
        m_acceleration.z += -glm::sin(glm::radians(rotation.y)) * speed;
    }
    if(glfwGetKey(theWindow, GLFW_KEY_D)==GLFW_PRESS) {
        m_acceleration.x += glm::cos(glm::radians(rotation.y)) * speed;
        m_acceleration.z += glm::sin(glm::radians(rotation.y)) * speed;
    }

    if(glfwGetKey(theWindow, GLFW_KEY_SPACE)==GLFW_PRESS) {
        jump();
    }
    else if(glfwGetKey(theWindow, GLFW_KEY_LEFT_SHIFT)==GLFW_PRESS && m_isFlying) {
        m_acceleration.y -= speed * 3;
    }
}

void Player::mouseInput()
{
    static bool useMouse = true;
/*
    if(glfwGetKey(theWindow, GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS) {
        useMouse = !useMouse;
    }

    if (!useMouse) {
        return;
    }
*/
    static float const BOUND = 89.f;
    
    double xpos, ypos;
    glfwGetCursorPos(theWindow, &xpos, &ypos);

    double changeX = xpos - lastMousePositionX;
    double changeY = ypos - lastMousePositionY;

    rotation.y += changeX * 0.05f;
    rotation.x += changeY * 0.05f;

    if (rotation.x > BOUND)
        rotation.x = BOUND;
    else if (rotation.x < -BOUND)
        rotation.x = -BOUND;

    if (rotation.y > 360)
        rotation.y = 0;
    else if (rotation.y < 0)
        rotation.y = 360;

    int width, height;
    glfwGetWindowSize(theWindow, &width, &height);

    double cx = static_cast<double>(width / 2);
    double cy = static_cast<double>(height / 2);

    glfwSetCursorPos(theWindow, cx, cy);

    glfwGetCursorPos(theWindow, &lastMousePositionX, &lastMousePositionY);
}

void Player::draw(RenderMaster &master)
{
    for (unsigned i = 0; i < m_items.size(); i++) {
        Text* t = m_itemText[i];
        if (i == (unsigned)m_heldItem) {
            t->setColor(glm::vec4(0.0,1.0,0.0,1.0));
        }
        else {
            t->setColor(glm::vec4(0.0,0.0,1.0,1.0));
        }
        t->setTextValue((m_items[i].getMaterial().name) + " " +
                    std::to_string(m_items[i].getNumInStack()) + " ");
        // master.drawSFML(t);
        master.addText(t);
    }
    std::ostringstream stream;
    stream << " X: " << position.x << " Y: " << position.y
           << " Z: " << position.z << " Grounded " << std::boolalpha
           << m_isOnGround;

    m_posPrint.setTextValue(stream.str());
    master.addText(&m_posPrint);
}

void Player::jump()
{
    if (!m_isFlying) {
        if (m_isOnGround) {

            m_isOnGround = false;
            m_acceleration.y += speed * 50;
        }
    }
    else {
        m_acceleration.y += speed * 3;
    }
}

void Player::setWindow(GLFWwindow* newWindow){

    theWindow = newWindow;

}

GLFWwindow* Player::getWindow(){

    return theWindow;

}
