#include "../Inc/Enemy.h"

void Enemy::AIaction(glm::vec3 playerPos)
    {
        this->faceDirection = glm::normalize(playerPos-this->pos);
        if(this->movementSpeed.y==0.0){
        if((this->blocked[0]==1||this->blocked[1]==1||this->blocked[2]==1||this->blocked[3]==1))
        {
            this->movementForce.y=5.0;
        }
        }
        if(glm::length(playerPos-this->pos)>reactionDistance)
        {
            this->movementSpeed = this->faceDirection*this->defaultSpeed;
        }
        else
        {
            //this->movementSpeed = glm::cross(this->faceDirection,this->upDirection);
            this->movementSpeed=glm::vec3(0.0);
            if(this->attackDelay<=0.0)
            {
                this->attackDelay=this->defaultAttackDelay;
                this->shoot();
            }
        }
    }

    Enemy::Enemy(World* world, float gameSp, AssimpModel* modal, glm::vec3 pos, float dimensions, int health, int regen, int energy, int energyRegen, float speed,
          float damage, float reactionD, float attackDel, int attackCost,
          glm::vec3 faceFront, glm::vec3 up) : Entity(world, gameSp,modal,pos, dimensions,
                      health, regen, energy, energyRegen,speed, damage, attackDel, attackCost,up)
    {
        this->reactionDistance=reactionD;
    }

    void Enemy::update(glm::vec3 playerPos, float deltaTime)
    {
        if(this->iteration>10)
        {
            this->AIaction(playerPos);
            this->generalUpdate(deltaTime);
            this->collisionDetection(deltaTime);
            this->updateMovement(deltaTime);
            updateModel();
        }
        else
        {
            this->iteration++;
        }
    }

    /*void Enemy::drawEnemyBullets(Shader* shad, Player* player,float deltaTime)
    {
        glm::mat4 bulletMat = glm::mat4(1.0);
        float len = 0;
        float* lenPoint = &len;
        int bulletAmount = this->allBullets.size();
        glm::vec3 plPos = player->getPos();
        glm::vec3 plSiz = player->getHitBox();
        int plHp = player->getHp();
        float plDmg = player->getTakenDmg();
        for(int i = bulletAmount; i--;)
        {
            allBullets[i]->pos+=(allBullets[i]->direction*allBullets[i]->speed*deltaTime);
            bulletMat = glm::mat4(1.0);
            bulletMat = glm::translate(bulletMat,allBullets[i]->pos);
            bulletMat = bulletMat * allBullets[i]->rotation;
            bulletMat = glm::scale(bulletMat,allBullets[i]->siz);
            shad->setMat4(bulletMat,"modelMatrix");
            shad->setVec4f(allBullets[i]->col,"lCol");
            shad->set1i(0,"useText");
            shad->use();
            glDrawArrays(GL_TRIANGLES,0,sizeof(basicVertices));

            if(glm::length(plPos-this->allBullets[i]->pos)<50.0)
            {
                if(allBullets[i]->pos.x-allBullets[i]->siz.x<plPos.x+plSiz.x/2&&
                        allBullets[i]->pos.x+allBullets[i]->siz.x>plPos.x-plSiz.x/2&&
                        allBullets[i]->pos.y-allBullets[i]->siz.y<plPos.y+plSiz.y/2&&
                        allBullets[i]->pos.y+allBullets[i]->siz.y>plPos.y-plSiz.y/2&&
                        allBullets[i]->pos.z-allBullets[i]->siz.z<plPos.z+plSiz.z/2&&
                        allBullets[i]->pos.z+allBullets[i]->siz.z>plPos.z-plSiz.z/2)
                {
                    allBullets.erase(allBullets.begin()+i);
                    player->setTakenDmg(plDmg+this->damage);
                    //player->movementForce = (plDmg/4.0f)*glm::normalize(glm::vec3(plPos.x,plPos.y+plSiz.y*0.1,plPos.z)-allBullets[i]->pos);
                    if(plHp-this->damage<0)
                    {
                        player->setHp(0);
                    }
                    else
                    {
                        //player->setHp(plHp-this->damage);
                    }
                    continue;
                }
            }
            *lenPoint = glm::length(allBullets[i]->pos);
            if(len>1000.0)
            {
                this->allBullets.erase(this->allBullets.begin()+i);
                continue;
            }
        }
    }*/

    void Enemy::drawEnemy(Shader* shad1,unsigned int addVao)
    {
        glBindVertexArray(addVao);
        this->draw(shad1);
        //this->drawEnemyBullets(shad2, daPlayer,deltaTime);
    }
