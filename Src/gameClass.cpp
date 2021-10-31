#include "../Inc/gameClass.h"

Game::Game(const char* title,
           const int windowW, const int windowH,
           const int glMajor, const int glMinor)
{
    this->windowWidth = windowW;
    this->windowHeight = windowH;
    this->GLFWminorVersion = glMinor;
    this->GLFWminorVersion = glMajor;
    std::cout<<"constr1"<<std::endl;
    this->setGLFW(title, windowW, windowH, glMajor, glMinor);
    std::cout<<"constr2"<<std::endl;
    this->enableModes();
    std::cout<<"constr3"<<std::endl;
}
Game::~Game()
{

    glfwDestroyWindow(this->windax);
    glfwTerminate();
}

glm::mat4 Game::getPerspective(float halfAngle,float aspect, float closeP, float farP)
{

    glm::mat4 perspectiveMat = glm::mat4(1.0);

    //giving values
    perspectiveMat[2][3] = -1.0;
    perspectiveMat[2][2] = -(farP/(farP-closeP));
    perspectiveMat[3][2] = -((farP*closeP)/(farP-closeP));
    perspectiveMat[0][0] = ((1/tan(halfAngle/2))/aspect);
    perspectiveMat[1][1] = (1/tan(halfAngle/2));
    return perspectiveMat;
}

void Game::bulletUpdate(std::vector<Bullet*>& playerBulletArr,std::vector<Bullet*>& enemyBulletArr, glm::vec2 blockSize,std::vector<levelObject*> levelObjects)
{
    int iterationMoveVal = 0;
    //Entity bullet colllision
    for(int i =0; i<levelObjects.size(); i++)
    {
        for(int b = playerBulletArr.size(); b--;)
        {
            if(playerBulletArr[b]->pos.x<levelObjects[i]->pos.x+(blockSize.x/2)&&
                    playerBulletArr[b]->pos.x>levelObjects[i]->pos.x-(blockSize.x/2)&&
                    playerBulletArr[b]->pos.y<levelObjects[i]->pos.y+(blockSize.y/2)&&
                    playerBulletArr[b]->pos.y>levelObjects[i]->pos.y-(blockSize.y/2))
            {
                //level->setDestroyedBlock(levelObjects[i]->type,levelObjects[i]->biomeNum,levelObjects[i]->chunkNum,levelObjects[i]->columnNum,levelObjects[i]->num);
                playerBulletArr.erase(playerBulletArr.begin()+b);
                break;
            }
        }

        for(int b = enemyBulletArr.size(); b--;)
        {
            if(enemyBulletArr[b]->pos.x<levelObjects[i]->pos.x+(blockSize.x/2)&&
                    enemyBulletArr[b]->pos.x>levelObjects[i]->pos.x-(blockSize.x/2)&&
                    enemyBulletArr[b]->pos.y<levelObjects[i]->pos.y+(blockSize.y/2)&&
                    enemyBulletArr[b]->pos.y>levelObjects[i]->pos.y-(blockSize.y/2))
            {
                //level->setDestroyedBlock(levelObjects[i]->type,levelObjects[i]->biomeNum,levelObjects[i]->chunkNum,levelObjects[i]->columnNum,levelObjects[i]->num);
                enemyBulletArr.erase(enemyBulletArr.begin()+b);
                break;
            }
        }
    }
}

//window setup

void Game::setGLFW(const char* windwName, const int width, const int height, const int majorVersion, const int minorVersion)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES,4);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    this->windax = glfwCreateWindow(width, height, windwName, NULL, NULL);

    glfwGetFramebufferSize(windax, &framebufferWidth, &framebufferHeight);
    glfwSetFramebufferSizeCallback(windax, frameBufferRez);

    glfwMakeContextCurrent(this->windax); //Important!!!!

    //GLAD check
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glfwSetInputMode(this->windax, GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    //glfwSetCursorPosCallback(this->windax, mouseInput);
    glfwSetScrollCallback(this->windax, scrollInput);
}
void Game::enableModes()
{
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_FRAMEBUFFER_SRGB);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int Game::setShader(const char* vertexFile, const char* fragmentFile, int useGeometryShader, const char* geometryFile)
{
    this->allShaders.push_back(new Shader(vertexFile,fragmentFile, geometryFile, useGeometryShader));

    return (this->allShaders.size()-1);
}

int Game::setTexture2D(const char* texturePath)
{

    this->allTextures.push_back(new Texture(texturePath,GL_TEXTURE_2D,this->allTextures.size()));

    //renderer2D
    this->renderer2D.setTexture(this->allTextures[(this->allTextures.size()-1)]);

    return (this->allTextures.size()-1);
}

void Game::initRenderer(const char* fontPath, const char* vertexPath, const char* fragPath)
{

    this->renderer2D.init(fontPath, vertexPath, fragPath);

}

void Game::setSkyBoxTexture(const char* leftTexturePath, const char* rightTexturePath, const char* topTexturePath,
                            const char* bottomTexturePath, const char* frontTexturePath, const char* backTexturePath)
{

    unsigned int cubeText;
    glGenTextures(1,&this->skyboxTexture);

    this->skyboxTexture = SOIL_load_OGL_cubemap(leftTexturePath, rightTexturePath, topTexturePath, bottomTexturePath,
                          frontTexturePath, backTexturePath, SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    glBindTexture(GL_TEXTURE_CUBE_MAP,this->skyboxTexture);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
}

void Game::setDefaultShaderValues()
{

    glm::mat4 proj = glm::ortho(0.0f, float(this->windowWidth), 0.0f, float(this->windowHeight),-1.0f,1.0f);
    this->allShaders[BASIC_2D_PROG]->setMat4(proj,"projectionMatrix");
}

void Game::setVAOs()
{
    unsigned int basicVAO;
    glGenVertexArrays(1, &basicVAO);
    glBindVertexArray(basicVAO);

    GLuint basicVBO;
    glGenBuffers(1, &basicVBO);
    glBindBuffer(GL_ARRAY_BUFFER, basicVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(basicVertices), basicVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(basicVertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE, sizeof(basicVertex), (void*)offsetof(basicVertex, textr));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,3, GL_FLOAT, GL_FALSE, sizeof(basicVertex), (void*)offsetof(basicVertex, norm));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    this->allVAOs.push_back(basicVAO);
    this->allVBOs.push_back(basicVBO);

    unsigned int screenVAO, screenVBO;
    glGenVertexArrays(1, &screenVAO);
    glBindVertexArray(screenVAO);
    glGenBuffers(1, &screenVBO);

    glBindBuffer(GL_ARRAY_BUFFER, screenVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(screenVertices), screenVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(screenVertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE, sizeof(screenVertex), (void*)offsetof(screenVertex, textr));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    this->allVAOs.push_back(screenVAO);
    this->allVBOs.push_back(screenVBO);

    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

    this->allVAOs.push_back(skyboxVAO);
    this->allVBOs.push_back(skyboxVBO);

}

void Game::setUniforms()
{
    this->allShaders[BASIC_PROG]->setUb("matrixes",0);
    this->allShaders[MODEL_PROG]->setUb("matrixes",0);
    this->allShaders[CUBETEXT_PROG]->setUb("matrixes",0);
    glGenBuffers(1,&matrixUbo);
    glBindBuffer(GL_UNIFORM_BUFFER,matrixUbo);
    glBufferData(GL_UNIFORM_BUFFER,2*sizeof(glm::mat4),NULL,GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER,0);
    glBindBufferRange(GL_UNIFORM_BUFFER,0,matrixUbo,0,2*sizeof(glm::mat4));
}

void Game::setScreen()
{
    //rbo
    glGenRenderbuffers(1,&this->RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, this->RBO);
    glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,windowWidth,windowHeight);
    glBindRenderbuffer(GL_RENDERBUFFER,0);

    //FBOs
    glGenFramebuffers(1,&this->basicFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, this->basicFBO);
    //texture
    glGenTextures(1, &this->screenTexture);
    glBindTexture(GL_TEXTURE_2D,this->screenTexture);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA16F,windowWidth,windowHeight,0,GL_RGBA,GL_FLOAT,NULL);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,this->screenTexture,0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,this->RBO);
    unsigned int attachment = GL_COLOR_ATTACHMENT0;
    glDrawBuffers(1, &attachment);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout<<"ERROR:FRAMEBUFFER1:Framebuffer is not complete!"<<std::endl;
    }
    glGenRenderbuffers(1,&this->mRBO);
    glBindRenderbuffer(GL_RENDERBUFFER,this->mRBO);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER,4,GL_DEPTH24_STENCIL8,this->windowWidth,this->windowHeight);
    glBindRenderbuffer(GL_RENDERBUFFER,this->mRBO);
    glGenFramebuffers(1,&this->mFBO);
    glBindFramebuffer(GL_FRAMEBUFFER,this->mFBO);
    glGenTextures(1,&this->mFBOtext);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE,this->mFBOtext);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE,4,GL_RGB,this->windowWidth,this->windowHeight,GL_TRUE);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE,0);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D_MULTISAMPLE,this->mFBOtext,0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,this->mRBO);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "ERROR::FRAMEBUFFER:: multisample Framebuffer is not complete!" << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void Game::setupPlayer(){
    daPlayer = new Player(this->windax,&this->renderer2D,this->theWorld,this->gameSpeed, this->allModels[0], &this->mainCamera,
                          glm::vec3(0.0,150.0,0.0),0.5f,50,2,100,2,15.0f,15.0f,2.0f);

}

void Game::setModel(const char* path)
{
    this->allModels.push_back(new AssimpModel(path));
}

void Game::setEnvironment()
{
    this->theWorld = new World(this->allTextures[ATLAS],this->playerPos);
}

void Game::setLevelData()
{
    this->setEnvironment();
}

void Game::updateUniforms()
{
    //Update framebuffer size and projection matrix
    glfwGetFramebufferSize(this->windax, &this->framebufferWidth, &this->framebufferHeight);
    this->projectionMatrix = getPerspective(glm::radians(this->mainCamera.getZoom()),
                                            static_cast<float>(this->framebufferWidth)/this->framebufferHeight, this->nearPlane, this->farPlane);
    this->viewMatrix = this->mainCamera.getViewMatrix();

    //ubos
    glBindBuffer(GL_UNIFORM_BUFFER,this->matrixUbo);
    glBufferSubData(GL_UNIFORM_BUFFER,0,sizeof(glm::mat4),glm::value_ptr(this->projectionMatrix));
    glBufferSubData(GL_UNIFORM_BUFFER,sizeof(glm::mat4),sizeof(glm::mat4),glm::value_ptr(this->viewMatrix));
    glBindBuffer(GL_UNIFORM_BUFFER,0);
}

void Game::updateTime()
{
    this->currentTime = glfwGetTime();
    this->deltaTime = (currentTime - lastTime);
    this->lastTime = currentTime;

    if(this->deltaTime>1.0)
    {
        this->deltaTime=1.0;
    }
}

void Game::updateViewport()
{
    glfwGetFramebufferSize(this->windax,&this->framebufferWidth,&this->framebufferHeight);
    if(this->windowWidth != this->framebufferWidth||this->windowHeight != this->framebufferHeight)
    {
        this->windowWidth = this->framebufferWidth;
        this->windowHeight = this->framebufferHeight;

        this->setDefaultShaderValues();
        //this->projectionMatrix = glm::ortho(0.0f, float(this->windowWidth),float(this->windowHeight),0.0f,-1.0f,1.0f);

        glBindRenderbuffer(GL_RENDERBUFFER, this->RBO);
        glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,this->windowWidth,this->windowHeight);
        glBindRenderbuffer(GL_RENDERBUFFER,0);

        glBindTexture(GL_TEXTURE_2D,this->screenTexture);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA16F,this->windowWidth,this->windowHeight,0,GL_RGBA,GL_FLOAT,NULL);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindRenderbuffer(GL_RENDERBUFFER,this->mRBO);
        glRenderbufferStorageMultisample(GL_RENDERBUFFER,4,GL_DEPTH24_STENCIL8,this->windowWidth,this->windowHeight);
        glBindRenderbuffer(GL_RENDERBUFFER,this->mRBO);

        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE,this->mFBOtext);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE,4,GL_RGB,this->windowWidth,this->windowHeight,GL_TRUE);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE,0);
    }
}

void Game::refreshGame()
{
    this->mode=2;
    this->allEnemies.clear();
    this->daPlayer->refresh(this->theWorld->setSpawn());
    this->enemyAmount = 0;
}

void Game::mouseInput()
{
    glfwGetCursorPos(this->windax,&this->mouseX, &this->mouseY);
    if(mode==1||mode==3)
    {
        mouseY = this->windowHeight-mouseY;
        if(this->mouseX>this->windowWidth)
        {
            this->mouseX=this->windowWidth;
        }
        if(this->mouseX<0)
        {
            this->mouseX=0;
        }
        if(this->mouseY>this->windowHeight)
        {
            this->mouseY=this->windowHeight;
        }
        if(this->mouseY<0)
        {
            this->mouseY=0;
        }
    }
    else if(mode==2)
    {
        if(this->firstMouse)
        {
            this->lastMouseX = this->mouseX;
            this->lastMouseY = this->mouseY;
            this->firstMouse=false;
        }
        this->mouseOffSetX=this->mouseX-this->lastMouseX;
        this->mouseOffSetY=this->lastMouseY-this->mouseY;
        this->lastMouseX = this->mouseX;
        this->lastMouseY = this->mouseY;
        this->daPlayer->mouseCommand(this->mouseOffSetX,this->mouseOffSetY);
    }
}

void Game::keyboardInput()
{
    if(glfwGetKey(windax, GLFW_KEY_ESCAPE)==GLFW_PRESS)
    {
        glfwSetWindowShouldClose(windax, true);
        glfwDestroyWindow(windax);
    }
    if(this->mode==2)
    {

    }
}

void Game::update()
{
    this->updateTime();
    this->mouseInput();
    this->keyboardInput();
    this->updateViewport();

    this->renderer2D.clearVerts();
    this->renderer2D.update(this->windowWidth,this->windowHeight);
    this->updateUniforms();
    if(mode==1)
    {
        cameraPos.x += this->deltaTime*2.0f;
        this->mainCamera.setPosition(this->cameraPos);
        this->mainCamera.setFront(glm::vec3(0.6,-1.0,0.0));
    }
    else if(mode==2)
    {
    }
}

void Game::renderBegin()
{
    glClearColor(0.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0,0,this->windowWidth,this->windowHeight);
    glBindFramebuffer(GL_FRAMEBUFFER,this->mFBO);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glClearColor(0.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

    glStencilFunc(GL_ALWAYS,1,0xFF);
    glStencilMask(0xFF);
}

void Game::renderEnd()
{
    glfwSwapBuffers(this->windax);
    glFlush();
    glfwPollEvents();
    glBindVertexArray(0);
    glUseProgram(0);
    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Game::generalGameUpdate()
{
    this->playerPos = this->daPlayer->getPos();
}

void Game::updateWorld()
{
    //main
    this->theWorld->update(this->playerPos,this->deltaTime);

}

void Game::updatePlayer()
{
    this->daPlayer->update(this->deltaTime,this->windowWidth,this->windowHeight);
}

void Game::updateEnemies()
{
    this->enemyCounter-=this->deltaTime;
    if(this->enemyCounter<=0.0&&this->enemyAmount<this->enemyLimit)
    {
        this->enemyAmount++;
        this->enemyCounter=30.0;
        float enX = ((2*(rand()%100))-100)+this->daPlayer->getPos().x;
        float enY = 30.0;
        float enZ = ((2*(rand()%100))-100)+this->daPlayer->getPos().z;
        this->allEnemies.push_back(new Enemy(this->theWorld,this->gameSpeed,this->allModels[0], glm::vec3(enX,enY,enZ),1.0,30,1,20,2,20.0,5.0,70.0f,20.0,5));
    }
    for(int e = enemyAmount; e--;)
    {
        this->allEnemies[e]->update(this->playerPos,this->deltaTime);
        glBindVertexArray(this->allVAOs[BASIC_VAO]);
        if(this->allEnemies[e]->getHp()<=0)
        {
            this->allEnemies.erase(this->allEnemies.begin()+e);
            enemyAmount--;
        }
    }
}

void Game::render()
{
    this->theWorld->drawMesh(this->allShaders[BASIC_PROG]);
    if(this->mode==2)
    {
        this->daPlayer->drawPlayer(this->allShaders[MODEL_PROG],this->allVAOs[BASIC_VAO]);
        for(int e = enemyAmount; e--;)
        {
            this->allEnemies[e]->drawEnemy(this->allShaders[MODEL_PROG],this->allVAOs[BASIC_VAO]);
        }
    }
}

void Game::renderBackground()
{
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_FALSE);
    this->viewMatrix = glm::mat4(glm::mat3(this->mainCamera.getViewMatrix()));
    this->allShaders[CUBETEXT_PROG]->set1i(0,"cubText");
    this->allShaders[CUBETEXT_PROG]->setMat4(this->viewMatrix,"viewMatrix");
    glBindVertexArray(this->allVAOs[SKYBOX_VAO]);
    this->allShaders[CUBETEXT_PROG]->use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->skyboxTexture);
    glDrawArrays(GL_TRIANGLES,0,sizeof(skyboxVertices));
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
}

void Game::renderScreenText()
{
    this->modelMatrix = glm::mat4(1.0);
    if(mode==1)
    {
        glm::vec3 daCol[5] = {glm::vec3(1.0,0.0,0.0),glm::vec3(1.0,0.0,0.0),glm::vec3(1.0,0.0,0.0),glm::vec3(1.0,0.0,0.0),glm::vec3(1.0,0.0,0.0)};
        if(this->mouseX>this->windowWidth*0.45&&this->mouseX<this->windowWidth*0.55)
        {
            if(this->mouseY<this->windowHeight*0.75&&this->mouseY>this->windowHeight*0.65)
            {
                daCol[0] = glm::vec3(1.0,1.0,0.0);
                if(glfwGetMouseButton(windax, GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS)
                {
                    this->refreshGame();
                }
            }
            else if(this->mouseY<this->windowHeight*0.6&&this->mouseY>this->windowHeight*0.5)
            {
                daCol[1] = glm::vec3(1.0,1.0,0.0);
                if(glfwGetMouseButton(windax, GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS)
                {

                }
            }
            else if(this->mouseY<this->windowHeight*0.45&&this->mouseY>this->windowHeight*0.35)
            {
                daCol[2] = glm::vec3(1.0,1.0,0.0);
                if(glfwGetMouseButton(windax, GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS)
                {

                }
            }
            else if(this->mouseY<this->windowHeight*0.3&&this->mouseY>this->windowHeight*0.2)
            {
                daCol[3] = glm::vec3(1.0,1.0,0.0);
                if(glfwGetMouseButton(windax, GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS)
                {

                }
            }
            else if(this->mouseY<this->windowHeight*0.15&&this->mouseY>this->windowHeight*0.05)
            {
                daCol[4] = glm::vec3(1.0,1.0,0.0);
                if(glfwGetMouseButton(windax, GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS)
                {
                    glfwSetWindowShouldClose(windax, true);
                    glfwDestroyWindow(windax);
                }
            }
        }
        //this->renderer2D.writeText("StuffCraft",0.5f,0.85f,3.0f,glm::vec3(1.0,0.0,0.0));
        this->renderer2D.writeText("Play",0.5f,0.65f,1.0f,daCol[0]);
        this->renderer2D.writeText("Difficulty",0.5f,0.5f,1.0f,daCol[1]);
        this->renderer2D.writeText("Settings",0.5f,0.35f,1.0f,daCol[2]);
        this->renderer2D.writeText("Stuff",0.5f,0.2f,1.0f,daCol[3]);
        this->renderer2D.writeText("Quit",0.5f,0.05f,1.0f,daCol[4]);
    }
    else if(mode == 2)
    {
        this->renderer2D.writeText("Health",0.2f,0.17f,0.5f,glm::vec3(1.0,0.0,0.0));
        this->renderer2D.writeText("Energy",0.6f,0.17f,0.5f,glm::vec3(1.0,0.0,0.0));
        this->renderer2D.writeText("FPS:",0.8f,0.9f,0.5f,glm::vec3(1.0,1.0,1.0));

        this->daPlayer->getInventory()->renderText();

        std::stringstream ms;
        std::string dif;
        ms<<((int)(1.0f/this->deltaTime));
        dif = ms.str();
        this->renderer2D.writeText(dif,0.9f,0.9f,0.5f,glm::vec3(1.0,1.0,1.0));
    }
    else if(mode == 3)
    {
        glm::vec3 daCol[5] = {glm::vec3(1.0,0.0,0.0),glm::vec3(1.0,0.0,0.0)};
        if(this->mouseY>this->windowHeight*0.35&&this->mouseY<this->windowHeight*0.45)
        {
            if(this->mouseX>this->windowWidth*0.35&&this->mouseX<this->windowWidth*0.45)
            {
                daCol[0] = glm::vec3(1.0,1.0,0.0);
                if(glfwGetMouseButton(windax, GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS)
                {
                    this->refreshGame();
                }
            }
            else if(this->mouseX>this->windowWidth*0.6&&this->mouseX<this->windowWidth*0.7)
            {
                daCol[1] = glm::vec3(1.0,1.0,0.0);
                if(glfwGetMouseButton(windax, GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS)
                {
                    this->mode=1;
                }
            }
        }
        this->renderer2D.writeText("Dead",0.5f,0.6f,3.0f,glm::vec3(1.0,0.0,0.0));
        this->renderer2D.writeText("Play again",0.4f,0.4f,2.0f,daCol[0]);
        this->renderer2D.writeText("Menu",0.6f,0.4f,2.0f,daCol[1]);
    }
}

void Game::renderScreenAdditions()
{
    if(this->mode==1)
    {
        this->renderer2D.setBasicSprite(0.5f,0.9f, 0.7f,0.5f, glm::vec4(1.0,1.0,1.0,1.0), 2);

        this->renderer2D.setBasicSprite(0.5f,0.67f, 0.42f,0.12f, glm::vec4(0.4,0.4,0.4,1.0), 16);
        this->renderer2D.setBasicSprite(0.5f,0.67f, 0.4f,0.1f, glm::vec4(0.8,0.8,0.8,1.0), 16);

        this->renderer2D.setBasicSprite(0.5f,0.52f, 0.42f,0.12f, glm::vec4(0.4,0.4,0.4,1.0), 16);
        this->renderer2D.setBasicSprite(0.5f,0.52f, 0.4f,0.1f, glm::vec4(0.8,0.8,0.8,1.0), 16);

        this->renderer2D.setBasicSprite(0.5f,0.37f, 0.42f,0.12f, glm::vec4(0.4,0.4,0.4,1.0), 16);
        this->renderer2D.setBasicSprite(0.5f,0.37f, 0.4f,0.1f, glm::vec4(0.8,0.8,0.8,1.0), 16);

        this->renderer2D.setBasicSprite(0.5f,0.22f, 0.42f,0.12f, glm::vec4(0.4,0.4,0.4,1.0), 16);
        this->renderer2D.setBasicSprite(0.5f,0.22f, 0.4f,0.1f, glm::vec4(0.8,0.8,0.8,1.0), 16);

        this->renderer2D.setBasicSprite(0.5f,0.07f, 0.42f,0.12f, glm::vec4(0.4,0.4,0.4,1.0), 16);
        this->renderer2D.setBasicSprite(0.5f,0.07f, 0.4f,0.1f, glm::vec4(0.8,0.8,0.8,1.0), 16);

        this->renderer2D.setBasicSprite((float)mouseX/(float)this->windowWidth,(float)mouseY/(float)this->windowHeight,
                                        0.01f,0.01f, glm::vec4(1.0,0.0,0.0,1.0), 16);
    }
    else
    {
        //health bar
        this->renderer2D.setBasicSprite(0.35f,0.18f,0.2f,0.02f, glm::vec4(1.0,0.0,0.0,1.0), 16);
        this->renderer2D.setBasicSprite(0.35f-(0.2*(0.5f-(float)daPlayer->getHp()/daPlayer->getFullHp()/2)),0.18f,
                                        0.2f*((float)daPlayer->getHp()/daPlayer->getFullHp()),0.02f, glm::vec4(0.0,1.0,0.0,1.0), 16);

        //energy bar
        this->renderer2D.setBasicSprite(0.75f,0.18f,0.2f,0.02f, glm::vec4(0.5,0.5,0.5,1.0), 16);
        this->renderer2D.setBasicSprite(0.75f-(0.2f*(0.5f-(float)daPlayer->getEnergy()/daPlayer->getFullEnergy()/2)),0.18f,
                                        0.2f*((float)daPlayer->getEnergy()/daPlayer->getFullEnergy()),0.02f, glm::vec4(1.0,1.0,0.0,1.0), 16);

        //aim
        this->renderer2D.setBasicSprite(0.5f,0.5f, 0.002f,0.03f, glm::vec4(0.0,0.0,0.0,1.0), 16);
        this->renderer2D.setBasicSprite(0.5f,0.5f, 0.03f,0.002f, glm::vec4(0.0,0.0,0.0,1.0), 16);
    }
    this->renderer2D.render2D(this->allShaders[BASIC_2D_PROG]);
}


void Game::renderScreen()
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER,mFBO);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER,basicFBO);
    glBlitFramebuffer(0,0,this->windowWidth,this->windowHeight,0,0,this->windowWidth,this->windowHeight,GL_COLOR_BUFFER_BIT,GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glClearColor(0.0,0.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0,0,this->windowWidth,this->windowHeight);
    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(this->allVAOs[SCREEN_VAO]);
    this->allShaders[SCREEN_PROG]->set1i(0,"textr");
    if(mode==3)
    {
        this->allShaders[SCREEN_PROG]->set1i(3,"mode");
    }
    else
    {
        this->allShaders[SCREEN_PROG]->set1i(this->mode,"mode");
    }
    this->allShaders[SCREEN_PROG]->setMat4(glm::mat4(1.0),"modelMatrix");
    this->allShaders[SCREEN_PROG]->setVec4f(glm::vec4(1.0,1.0,1.0,1.0),"additionalCol");
    if(mode==3)
    {
        this->allShaders[SCREEN_PROG]->set1f(0.5,"exposure");
    }
    else
    {
        if(this->daPlayer->getInventory()->checkIfOpen())
        {
            this->allShaders[SCREEN_PROG]->set1f(0.2,"exposure");
        }
        else
        {
            this->allShaders[SCREEN_PROG]->set1f(0.7,"exposure");
        }
    }
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->screenTexture);
    this->allShaders[SCREEN_PROG]->use();
    glDrawArrays(GL_TRIANGLES,0,sizeof(screenVertices));
}

void Game::renderGame()
{
    this->update();
    std::cout<<"update1"<<std::endl;
    this->renderBegin();
    std::cout<<"update2"<<std::endl;
    if(this->mode==2)
    {
        this->generalGameUpdate();
    }
    std::cout<<"update3"<<std::endl;
    this->updateWorld();
    std::cout<<"update4"<<std::endl;
    //this->threads.push_back(std::thread(&Game::updateWorld,this));
    //this->threads.push_back(std::thread(&Game::updatePlayer,this));
    //this->threads.push_back(std::thread(&Game::updateEnemies,this));
    if(this->mode==2)
    {
        this->updatePlayer();
        //this->updateEnemies();
    }
    std::cout<<"update5"<<std::endl;
    this->render();
    std::cout<<"update6"<<std::endl;
    this->renderBackground();
    std::cout<<"update7"<<std::endl;
    this->renderScreen();
    std::cout<<"update8"<<std::endl;
    this->renderScreenAdditions();
    std::cout<<"update9"<<std::endl;
    this->renderScreenText();
    std::cout<<"update10"<<std::endl;
    this->renderEnd();
}

void Game::setBasicProgram(int newVal)
{

    this->BASIC_PROG = newVal;
}
void Game::setBasic2DProgram(int newVal)
{

    this->BASIC_2D_PROG = newVal;
}
void Game::setCubeTextureProgram(int newVal)
{

    this->CUBETEXT_PROG = newVal;
}
void Game::setModelProgram(int newVal)
{

    this->MODEL_PROG = newVal;
}
void Game::setScreenProgram(int newVal)
{

    this->SCREEN_PROG = newVal;
}

void Game::setAtlasTextureNum(int newVal)
{

    this->ATLAS = newVal;
}
void Game::setGameNameTextureNum(int newVal)
{

    this->NAME = newVal;
}
