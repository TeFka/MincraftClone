#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>

#include<ft2build.h>
#include FT_FREETYPE_H

#include "../Text.h"

#include <vector>

#include "../Entity.h"
#include "../Item/ItemStack.h"

class World;
class RenderMaster;

/// @brief Player character, including player movements and world interactions.
class Player : public Entity {
  public:
  
    Player();

    void handleInput();

    void update(float dt, World &wolrd);
    void collide(World &world, const glm::vec3 &vel, float dt);

    void addItem(const Material &material);

    void draw(RenderMaster &master);

    ItemStack &getHeldItems();

    void setWindow(GLFWwindow*);
    GLFWwindow* getWindow();

  private:

    GLFWwindow* theWindow;

    Text playerText;
    Text m_posPrint;

    void jump();

    void keyboardInput();
    void mouseInput();
    bool m_isOnGround = false;
    bool m_isFlying = false;
    bool m_isSneak = false;

    std::vector<ItemStack> m_items;
    std::vector<Text*> m_itemText;
    int m_heldItem = 0;

    glm::vec3 m_acceleration;

    double lastMousePositionX;
    double lastMousePositionY;
};

#endif // PLAYER_H_INCLUDED
