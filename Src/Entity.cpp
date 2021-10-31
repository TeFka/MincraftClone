#include "../Inc/Entity.h"

Entity::Entity(World* world,float gameSp, AssimpModel* modal, glm::vec3 pos, float sizeMult, int health, int regen, int energy, int energyRegen, float speed,
               float damage,float attackDel, int attackCost, glm::vec3 up)
{
    this->theWorld = world;
    this->gameSpeed = gameSp;
    //this->model = new AssimpModel(*modal);
    //this->model->setPos(pos);
    //this->model->setSizeIncrease(sizeMult);

    float randX = ((float)(rand()%100))/100+0.01;
    float randZ = ((float)(rand()%100))/100+0.01;
    this->pos=pos;
    this->previousPos = pos;
    this->hitbox = sizeMult*modal->getBaseSize();
    this->modelMatrix = glm::mat4(1.0);

    this->faceDirection=glm::vec3(randX,0.0,randZ);
    this->upDirection=up;

    this->defaultAttackDelay = attackDel;
    this->attackDelay = attackDel;
    this->damage = damage;

    this->healthRegeneration = regen;
    this->health=health;
    this->fullHealth = health;

    this->fullEnergy = energy;
    this->energy = energy;
    this->energyRegeneration = energyRegen;
    this->attackCost = attackCost;

    this->defaultSpeed = speed;

    this->exsist=1;
}

void Entity::generalUpdate(float deltaTime)
{
    if(this->attackDelay>0.0)
    {
        this->attackDelay-=deltaTime;
    }

    if(this->health<this->fullHealth)
    {
        this->healthCounter+=deltaTime;
        if(this->healthCounter>1.0)
        {
            //this->health+=this->healthRegeneration;
            this->healthCounter=0;
        }
    }

    if(this->energy<this->fullEnergy)
    {
        this->energyCounter+=deltaTime;
        if(this->energyCounter>1.0)
        {
            this->energy+=this->energyRegeneration;
            this->energyCounter=0;
        }
    }

    this->movementForce.y -= GRAVITY*deltaTime*gameSpeed;

    //wind resistance
    this->movementForce.x -= 0.1*this->movementSpeed.x*(this->movementForce.x>0.05||this->movementForce.x<-0.05)*deltaTime*gameSpeed;
    this->movementForce.y -= 0.1*this->movementSpeed.y*(this->movementForce.y>0.05||this->movementForce.y<-0.05)*deltaTime*gameSpeed;
    this->movementForce.z -= 0.1*this->movementSpeed.z*(this->movementForce.z>0.05||this->movementForce.z<-0.05)*deltaTime*gameSpeed;


    this->movementSpeed+=(movementForce*deltaTime);
}

void Entity::updateMovement(float deltaTime)
{
    this->pos+=(movementSpeed*deltaTime*this->gameSpeed);
}

void Entity::collisionDetection(float deltaTime)
{
    int blockType;
    int minX = this->pos.x - (this->hitbox.x/2)-2;
        int minZ = this->pos.z - (this->hitbox.z/2)-2;
        int minY = this->pos.y - (this->hitbox.y/2)-2;
        int maxX = this->pos.x + (this->hitbox.x/2)+2;
        int maxZ = this->pos.z + (this->hitbox.z/2)+2;
        int maxY = this->pos.y + (this->hitbox.y/2)+2;
        for (int y = minY; y <= maxY; y++)
        {
            for (int x = minX; x <= maxX; x++)
            {
                for (int z = minZ; z <= maxZ; z++)
                {
                    blockType = this->theWorld->getBlock(x,y,z);
                    //std::cout<<"check pos: "<<x<<"  "<<y<<"  "<<z<<std::endl;
                    if(this->theWorld->bDatabase.blockTypes[blockType].canColide)
                    {
                        //Entity collision
                        //X axis
                        if(this->pos.y<y+BLOCK_HALF_SIZE&&
                                this->pos.y>=y-BLOCK_HALF_SIZE)
                        {
                            if(this->pos.z<z+BLOCK_HALF_SIZE&&
                                    this->pos.z>=z-BLOCK_HALF_SIZE)
                            {
                                //positive x
                                if((this->pos.x+this->hitbox.x/2+(this->movementSpeed.x*deltaTime)>x-BLOCK_HALF_SIZE&&
                                        this->pos.x+this->hitbox.x/2+(this->movementSpeed.x*deltaTime)<x+BLOCK_HALF_SIZE)||
                                   this->previousPos.x<x&&this->pos.x>x)
                                {
                                    if(this->movementForce.x>0.0)
                                    {
                                        this->movementForce.x=0.0;
                                    }
                                    this->pos.x=x-BLOCK_HALF_SIZE-(this->hitbox.x/2);
                                    this->movementSpeed.x=0.0;
                                }
                                //negative X
                                if((this->pos.x-this->hitbox.x/2-(this->movementSpeed.x*deltaTime)<x+BLOCK_HALF_SIZE&&
                                        this->pos.x-this->hitbox.x/2-(this->movementSpeed.x*deltaTime)>x-BLOCK_HALF_SIZE)||
                                   this->previousPos.x>x&&this->pos.x<x)
                                {
                                    if(this->movementForce.x<0.0)
                                    {
                                        this->movementForce.x=0.0;
                                    }
                                    this->pos.x=x+BLOCK_HALF_SIZE+(this->hitbox.x/2);
                                    this->movementSpeed.x=0.0;
                                }
                            }
                        }
                        // Y axis
                        if(this->pos.x<x+BLOCK_HALF_SIZE&&
                                this->pos.x>=x-BLOCK_HALF_SIZE)
                        {
                            if(this->pos.z<z+BLOCK_HALF_SIZE&&
                                    this->pos.z>=z-BLOCK_HALF_SIZE)
                            {
                                /*if(this->pos.y>y&&this->previousPos.y<y)
                                {
                                    this->pos.y=y-BLOCK_HALF_SIZE-(this->hitbox.y/2);
                                }
                                else
                                {*/
                                    //positive Y
                                    if((this->pos.y+this->hitbox.y/2+(this->movementSpeed.y*deltaTime)>y-BLOCK_HALF_SIZE&&
                                            this->pos.y+this->hitbox.y/2<y+BLOCK_HALF_SIZE)||
                                   this->previousPos.y<y&&this->pos.y>y)
                                    {
                                        if(this->movementForce.y>0.0)
                                        {
                                            this->movementForce.y=0.0;
                                        }
                                        this->pos.y=y-BLOCK_HALF_SIZE-(this->hitbox.y/2);
                                        this->movementSpeed.y=0.0;
                                    }
                                    //negative Y
                                    if((this->pos.y-this->hitbox.y/2<y+BLOCK_HALF_SIZE&&
                                            this->pos.y-this->hitbox.y/2>y-BLOCK_HALF_SIZE)||
                                   this->previousPos.y>y&&this->pos.y<y)
                                    {
                                        if(this->movementForce.y<0.0)
                                        {
                                            this->movementForce.y=0.0;
                                        }
                                        this->pos.y=y+BLOCK_HALF_SIZE+(this->hitbox.y/2);
                                        this->movementSpeed.y=0.0;
                                    }
                                //}
                            }
                        }
                        //Z axis
                        if(this->pos.x<x+BLOCK_HALF_SIZE&&
                                       this->pos.x>=x-BLOCK_HALF_SIZE)
                        {
                            if(this->pos.y<y+BLOCK_HALF_SIZE&&
                                    this->pos.y>=y-BLOCK_HALF_SIZE)
                            {
                                //positive x
                                if((this->pos.z+this->hitbox.z/2+(this->movementSpeed.z*deltaTime)>z-BLOCK_HALF_SIZE&&
                                        this->pos.z+this->hitbox.z/2+(this->movementSpeed.z*deltaTime)<z+BLOCK_HALF_SIZE)||
                                   this->previousPos.z<z&&this->pos.z>z)
                                {
                                    if(this->movementForce.z>0.0)
                                    {
                                        this->movementForce.z=0.0;
                                    }
                                    this->pos.z=z-BLOCK_HALF_SIZE-(this->hitbox.z/2);
                                    this->movementSpeed.z=0.0;
                                }
                                //negative X
                                if((this->pos.x-this->hitbox.z/2-(this->movementSpeed.z*deltaTime)<z+BLOCK_HALF_SIZE&&
                                        this->pos.z-this->hitbox.z/2-(this->movementSpeed.z*deltaTime)>z-BLOCK_HALF_SIZE)||
                                   this->previousPos.z>z&&this->pos.z<z)
                                {
                                    if(this->movementForce.z<0.0)
                                    {
                                        this->movementForce.z=0.0;
                                    }
                                    this->pos.x=z+BLOCK_HALF_SIZE+(this->hitbox.z/2);
                                    this->movementSpeed.z=0.0;
                                }
                            }
                        }
                    }
                }
            }
        }
    this->previousPos=this->pos;
}

void Entity::shoot()
{
    this->energy-=attackCost;
    Bullet* bull = new Bullet{this->pos,glm::vec3(1.0),this->faceDirection, this->getRotation(glm::mat4(1.0), this->pos, this->pos+this->faceDirection),
                              this->bulletSpeed,glm::vec4(1.0,0.0,0.0,1.0),0,0};
    //this->allBullets.push_back(bull);
}

glm::vec3 Entity::getPos()
{
    return this->pos;
}

int Entity::getHp()
{
    return this->health;
}

int Entity::getFullHp()
{
    return this->fullHealth;
}

int Entity::getEnergy()
{
    return this->energy;
}

int Entity::getFullEnergy()
{
    return this->fullEnergy;
}

void Entity::setHp(int newHp)
{
    this->health = newHp;
}

float Entity::getTakenDmg()
{
    return this->takenDamage;
}

void Entity::setTakenDmg(float newDmg)
{
    this->takenDamage = newDmg;
}

glm::vec3 Entity::getHitBox()
{
    return this->hitbox;
}

void Entity::updateModel()
{
    this->model->setPos(this->pos);
    this->model->setFaceDir(this->faceDirection);
}

void Entity::draw(Shader* shader)
{
    this->model->Draw(shader);
}

glm::mat4 Entity::getRotation(glm::mat4 modal, glm::vec3 pos, glm::vec3 otherPos)
{
    float angle = glm::degrees(atan((pos.z-otherPos.z)/(otherPos.x-pos.x)));
    if(otherPos.x<pos.x)
    {
        angle+=90;
    }
    else if(otherPos.x>pos.x)
    {
        angle = -(90-angle);
    }
    else
    {
        if(otherPos.z>pos.z)
        {
            angle = 180;
        }
        else
        {
            angle = 0;
        }
    }
    return glm::rotate(modal, glm::radians(angle),glm::vec3(0.0,1.0,0.0));
}
