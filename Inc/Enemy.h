#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include"Entity.h"

class Enemy : public Entity
{

private:

    float reactionDistance;

    void AIaction(glm::vec3);

public:

    Enemy(World*,float, AssimpModel*, glm::vec3, float, int, int, int, int, float, float,
           float=20.0, float=20.0, int=10.0, glm::vec3=glm::vec3(1.0,0.0,0.0), glm::vec3=glm::vec3(0.0,1.0,0.0));

    void update(glm::vec3, float);

    //void drawEnemyBullets(Shader*, Player*,float);

    void drawEnemy(Shader*,unsigned int);
};

#endif // ENEMY_H_INCLUDED
