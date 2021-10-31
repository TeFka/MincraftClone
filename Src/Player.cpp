#include "../Inc/Player.h"

void Player::updateCamera()
{
    this->playerCamera->setPosition(this->pos);
    this->playerCamera->setFront(this->faceDirection);
}

void Player::updateFrontVec()
{
    glm::vec3 frontCm;
    this->rotationMatrix = glm::mat4(1.0);

    frontCm.x=cos(glm::radians(this->xRotation))*cos(glm::radians(this->yRotation));

    frontCm.y=sin(glm::radians(this->xRotation));

    frontCm.z=cos(glm::radians(this->xRotation))*sin(glm::radians(this->yRotation));

    this->faceDirection=-glm::normalize(frontCm);
}

void Player::sendRay()
{
    if(!this->rayShot)
    {
        this->rayDirection = this->faceDirection;
        this->rayPos = this->pos;
        this->rayOrgPos = this->pos;
        this->rayShot = 1;
    }
}

void Player::updateRay()
{
    if(this->rayShot)
    {
        //std::cout<<this->rayPos.x<<"  "<<this->rayPos.y<<"  "<<this->rayPos.z<<std::endl;
        this->rayPos+=(this->rayDirection);
        int bl = this->theWorld->getBlock((int)this->rayPos.x,(int)this->rayPos.y,(int)this->rayPos.z);
        if(this->theWorld->bDatabase.blockTypes[bl].canColide)
        {
            //std::cout<<"found block"<<std::endl;
            auto chunkPos = this->theWorld->getChunkXZ((int)this->rayPos.x, (int)this->rayPos.z);
            this->theWorld->deleteChunkMesh(chunkPos.x,chunkPos.z);
            this->theWorld->setBlock((int)this->rayPos.x,(int)this->rayPos.y,(int)this->rayPos.z,0);
            this->theWorld->getChunk(chunkPos.x,chunkPos.z).makeMesh();
            this->rayShot = 0;
            this->inventory->pushItem(bl);
        }
        if(length(this->rayPos-this->rayOrgPos)>5)
        {
            this->rayShot = 0;
        }
    }
}

Player::Player(GLFWwindow* windw, Renderer2D* rendr, World* world,float gameSp,AssimpModel* modal, Camera* cam,glm::vec3 pos, float dimensions,
               int health, int regen, int energy, int energyRegen, float speed,
               float damage,float attackDel, int attackCost,
               glm::vec3 faceFront, glm::vec3 up) : Entity(world,gameSp,modal, pos, dimensions,
                           health, regen, energy, energyRegen, speed, damage,attackDel, attackCost, up)
{
    this->inventory = new Inventory(rendr);
    this->playerCamera = cam;
    this->windowX = windw;
}

Inventory* Player::getInventory()
{
    return this->inventory;
}

void Player::keyboardCommand(float deltaTime)
{
    if(!this->inventory->checkIfOpen())
    {
        if(this->movementSpeed.y>=0.0)
        {
            if(glfwGetKey(this->windowX, GLFW_KEY_W)==GLFW_PRESS)
            {
                //this->pos+=(this->defaultSpeed*deltaTime*this->faceDirection);
                this->movementSpeed.x=(this->defaultSpeed*this->faceDirection).x;
                this->movementSpeed.z=(this->defaultSpeed*this->faceDirection).z;
            }
            else if(glfwGetKey(this->windowX, GLFW_KEY_S)==GLFW_PRESS)
            {
                this->movementSpeed.x=-(this->defaultSpeed*this->faceDirection).x;
                this->movementSpeed.z=-(this->defaultSpeed*this->faceDirection).z;
            }
            else if(glfwGetKey(this->windowX, GLFW_KEY_D)==GLFW_PRESS)
            {
                this->movementSpeed.x=(this->defaultSpeed*glm::normalize(glm::cross(this->faceDirection,this->upDirection))).x;
                this->movementSpeed.z=(this->defaultSpeed*glm::normalize(glm::cross(this->faceDirection,this->upDirection))).z;
            }
            else if(glfwGetKey(this->windowX, GLFW_KEY_A)==GLFW_PRESS)
            {
                this->movementSpeed.x=-(this->defaultSpeed*glm::normalize(glm::cross(this->faceDirection,this->upDirection))).x;
                this->movementSpeed.z=-(this->defaultSpeed*glm::normalize(glm::cross(this->faceDirection,this->upDirection))).z;
            }
            else
            {
                this->movementSpeed.x = 0.0;
                this->movementSpeed.z = 0.0;
            }
            if(this->movementSpeed.y==0.0)
            {
                if(glfwGetKey(this->windowX, GLFW_KEY_SPACE)==GLFW_PRESS)
                {
                    this->movementForce.y+=this->defaultSpeed/4;
                }
                if(glfwGetKey(this->windowX, GLFW_KEY_F)==GLFW_PRESS)
                {
                    this->pos.y-=0.2;
                }
            }
        }
        if(glfwGetMouseButton(this->windowX, GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS)
        {
            if(attackDelay<=0.0)
            {
                //std::cout<<"ray send"<<std::endl;
                this->attackDelay=this->defaultAttackDelay;
                this->sendRay();
            }
        }
    }
    else
    {
        this->movementSpeed.x = 0.0;
        this->movementSpeed.z = 0.0;
    }
    if(glfwGetKey(this->windowX, GLFW_KEY_E)==GLFW_PRESS)
    {
        if(!this->changedInventory)
        {
            if(this->inventory->checkIfOpen())
            {
                this->inventory->closeInventory();
            }
            else
            {
                this->inventory->openInventory();
            }
            this->changedInventory = 1;
        }
    }
    else
    {
        this->changedInventory = 0;
    }
}

void Player::mouseCommand(float xSet, float ySet, GLboolean pitchConstr)
{
    if(!this->inventory->checkIfOpen())
    {
        //this->playerCamera->mouseCall(xSet,ySet);
        xSet*=this->playerCamera->getSensetivity();
        ySet*=this->playerCamera->getSensetivity();

        xRotation-=ySet;
        yRotation+=xSet;

        if(pitchConstr)
        {
            if(xRotation>89.0)
            {
                xRotation=89.0;
            }
            if(xRotation<-89.0)
            {
                xRotation=-89.0;
            }
        }
        this->updateFrontVec();
        this->updateCamera();
    }
}

void Player::refresh(glm::vec3 pos)
{
    this->movementForce=glm::vec3(0.0);
    this->movementSpeed=glm::vec3(0.0);
    this->pos=pos;
    this->health = this->fullHealth;
    this->energy=this->fullEnergy;
    this->iteration=0;
    this->healthCounter=0;
    this->energyCounter=0;
    this->updateFrontVec();
    this->updateCamera();
}

void Player::update(float deltaTime,int windowWidth, int windowHeight)
{
    if(iteration>10)
    {
        this->inventory->update(windowWidth, windowHeight);
        this->keyboardCommand(deltaTime);
        this->generalUpdate(deltaTime);
        this->updateRay();
        this->collisionDetection(deltaTime);
        this->updateMovement(deltaTime);
        this->updateFrontVec();
        this->updateCamera();
        //this->updateModel();
    }
    else
    {
        iteration++;
    }
}

//void drawPlayerBullets(Shader*, std::vector<Enemy*>, float);
void Player::drawPlayer(Shader* shad1, unsigned int addVao)
{
    this->inventory->render();
    //draw(shad1);
}

