#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include"Camera.h"
#include"Entity.h"
#include"Inventory.h"
class Player : public Entity
{

private:
    float changedInventory = 0;
    int rayShot = 0;
    glm::vec3 rayPos;
    glm::vec3 rayOrgPos;
    glm::vec3 rayDirection;

    Inventory* inventory;
    Camera* playerCamera;
    GLFWwindow* windowX;

    void updateCamera();

    void updateFrontVec();

    void sendRay();
    void updateRay();

public:

    Player(GLFWwindow*, Renderer2D*, World*,float,AssimpModel*, Camera*,glm::vec3, float, int, int, int, int,
            float,float,float=10.0, int=10.0,glm::vec3=glm::vec3(1.0,0.0,0.0), glm::vec3=glm::vec3(0.0,1.0,0.0));

    Inventory* getInventory();
    void keyboardCommand(float);

    void mouseCommand(float, float, GLboolean = true);

    void refresh(glm::vec3);

    void update(float,int,int);

    //void drawPlayerBullets(Shader*, std::vector<Enemy*>, float);
    void drawPlayer(Shader*, unsigned int);
};

#endif // PLAYER_H_INCLUDED
