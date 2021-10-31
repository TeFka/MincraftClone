
#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include"Model.h"
#include"World.h"

//constants

class Enemy;

//functions

class Entity
{
    friend class Player;
    friend class Enemy;
protected:
    World* theWorld;
    int GRAVITY = 10.0;
    float gameSpeed;
    AssimpModel* model;
    glm::vec3 pos;
    glm::vec3 previousPos;

    float xRotation=0, yRotation=0, zRotation=0;
    glm::mat4 modelMatrix;
    glm::mat4 rotationMatrix;

    glm::vec3 hitbox;

    glm::vec3 faceDirection;
    glm::vec3 upDirection;

    float defaultSpeed;
    glm::vec3 movementSpeed=glm::vec3(0.0,0.0,0.0);
    glm::vec3 movementForce=glm::vec3(0.0,0.0,0.0);
    int blocked[4] = {0,0,0,0};

    int goBack = 0;
    float bulletSpeed = 10.0;

    float defaultAttackDelay;
    float attackDelay;
    float damage = 0;

    int fullHealth;
    int health;
    float healthCounter = 0;
    int healthRegeneration;
    float takenDamage = 0;

    int energy;
    int fullEnergy;
    float energyCounter = 0;
    int energyRegeneration;
    int attackCost;

    int exsist;

    int iteration = 0;

    glm::mat4 getRotation(glm::mat4, glm::vec3, glm::vec3);

    void generalUpdate(float);

    void updateMovement(float);

    void collisionDetection(float);

    void shoot();
public:
    Entity(World*,float, AssimpModel*, glm::vec3, float, int, int, int, int, float,float,
           float = 20.0, int=10.0, glm::vec3=glm::vec3(0.0,1.0,0.0));

    glm::vec3 getPos();

    int getHp();

    int getFullHp();

    int getEnergy();

    int getFullEnergy();

    void setHp(int);

    float getTakenDmg();

    void setTakenDmg(float);

    glm::vec3 getHitBox();

    void updateModel();

    void draw(Shader*);

};
#endif
