#ifndef GAMECLASS_H_INCLUDED
#define GAMECLASS_H_INCLUDED

#include <iostream>

#include"struct.h"
#include"Shader.h"
#include"Texture.h"
#include"Camera.h"
#include"Renderer2D.h"
#include"ChunkSection.h"
#include"chunkMap.h"
#include"Chunk.h"
#include"World.h"
#include"Entity.h"
#include"Player.h"
#include"Enemy.h"

class Game
{

private:

    //window data
    GLFWwindow* windax;
    int windowWidth;
    int windowHeight;
    int framebufferWidth = 0;
    int framebufferHeight = 0;
    int GLFWminorVersion;
    int GLFWmajorVersion;

    //camera values
    Camera mainCamera;
    glm::vec3 cameraPos = glm::vec3(0.0,130.0,0.0);

    // projection values
    float nearPlane = 0.1;
    float farPlane = 500.0;

    // time measuring
    float deltaTime;
    float lastTime;
    float currentTime;

    //game variables
    float gameSpeed = 1;
    glm::vec3 playerPos;
    float brickSize;
    // mouse information
    double mouseX;
    double mouseY;
    int lastMouseX;
    int lastMouseY;
    int mouseOffSetX;
    int mouseOffSetY;
    int firstMouse;

    // Matrices
    glm::mat4 modelMatrix = glm::mat4(1.0);
    glm::mat4 projectionMatrix = glm::mat4(1.0);
    glm::mat4 viewMatrix = glm::mat4(1.0);

    // Ubos
    unsigned int matrixUbo;
    unsigned int lightUbo;

    //skybox
    unsigned int skyboxTexture;

    //screen texture
    unsigned int basicFBO;
    unsigned int RBO;
    unsigned int screenTexture;

    unsigned int mFBO;
    unsigned int mRBO;
    unsigned int mFBOtext;

    //side variables
    int mode = 1;
    Renderer2D renderer2D;

    //side constants
    const int gravity = 10;

    basicVertex basicVertices[36]
{
    //front
    glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.0,1.0),glm::vec3(0.0, 0.0, 1.0),1.0,
    glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0,0.0),glm::vec3(0.0, 0.0, 1.0),1.0,
    glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1.0,0.0),glm::vec3(0.0, 0.0, 1.0),1.0,
    glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.0,1.0),glm::vec3(0.0, 0.0, 1.0),1.0,
    glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1.0,0.0),glm::vec3(0.0, 0.0, 1.0),1.0,
    glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0,1.0),glm::vec3(0.0, 0.0, 1.0),1.0,
    //back
    glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(0.0,1.0),glm::vec3(0.0, 0.0, -1.0),1.0,
    glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.0,0.0),glm::vec3(0.0, 0.0, -1.0),1.0,
    glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(1.0,0.0),glm::vec3(0.0, 0.0, -1.0),1.0,
    glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(0.0,1.0),glm::vec3(0.0, 0.0, -1.0),1.0,
    glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(1.0,0.0),glm::vec3(0.0, 0.0, -1.0),1.0,
    glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(1.0,1.0),glm::vec3(0.0, 0.0, -1.0),1.0,
    //left
    glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(0.0,1.0),glm::vec3(1.0, 0.0, 0.0),1.0,
    glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(0.0,0.0),glm::vec3(1.0, 0.0, 0.0),1.0,
    glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0,0.0),glm::vec3(1.0, 0.0, 0.0),1.0,
    glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(0.0,1.0),glm::vec3(1.0, 0.0, 0.0),1.0,
    glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0,0.0),glm::vec3(1.0, 0.0, 0.0),1.0,
    glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0,1.0),glm::vec3(1.0, 0.0, 0.0),1.0,
    //right
    glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0,1.0),glm::vec3(-1.0, 0.0, 0.0),1.0,
    glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0,0.0),glm::vec3(-1.0, 0.0, 0.0),1.0,
    glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(1.0,0.0),glm::vec3(-1.0, 0.0, 0.0),1.0,
    glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0,1.0),glm::vec3(-1.0, 0.0, 0.0),1.0,
    glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(1.0,0.0),glm::vec3(-1.0, 0.0, 0.0),1.0,
    glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(1.0,1.0),glm::vec3(-1.0, 0.0, 0.0),1.0,
    //bottom
    glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0,1.0),glm::vec3(0.0, -1.0, 0.0),1.0,
    glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0,0.0),glm::vec3(0.0, -1.0, 0.0),1.0,
    glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0,0.0),glm::vec3(0.0, -1.0, 0.0),1.0,
    glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0,1.0),glm::vec3(0.0, -1.0, 0.0),1.0,
    glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0,0.0),glm::vec3(0.0, -1.0, 0.0),1.0,
    glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1.0,1.0),glm::vec3(0.0, -1.0, 0.0),1.0,
    //top
    glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0,1.0),glm::vec3(0.0, 1.0, 0.0),1.0,
    glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.0,0.0),glm::vec3(0.0, 1.0, 0.0),1.0,
    glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0,0.0),glm::vec3(0.0, 1.0, 0.0),1.0,
    glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0,1.0),glm::vec3(0.0, 1.0, 0.0),1.0,
    glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0,0.0),glm::vec3(0.0, 1.0, 0.0),1.0,
    glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0,1.0),glm::vec3(0.0, 1.0, 0.0),1.0,
};

    float skyboxVertices[108] =
{
    // positions
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f
};

screenVertex screenVertices[6]
{
    glm::vec3(-1.0,1.0,0.0), glm::vec2(0.0,1.0),
    glm::vec3(-1.0,-1.0,0.0), glm::vec2(0.0,0.0),
    glm::vec3(1.0,-1.0,0.0), glm::vec2(1.0,0.0),
    glm::vec3(-1.0,1.0,0.0), glm::vec2(0.0,1.0),
    glm::vec3(1.0,-1.0,0.0), glm::vec2(1.0,0.0),
    glm::vec3(1.0,1.0,0.0), glm::vec2(1.0,1.0),
};

    GLuint cubSides[6] =
    {
        GL_TEXTURE_CUBE_MAP_POSITIVE_X,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
    };

    // IDs
    // Shaders
    int BASIC_PROG;
    int SCREEN_PROG;
    int CUBETEXT_PROG;
    int MODEL_PROG;
    int BASIC_2D_PROG;

    //VAOS

    const int BASIC_VAO = 0;
    const int SCREEN_VAO = 1;
    const int SKYBOX_VAO = 2;

    //Textures
    int ATLAS = 0;
    int NAME = 1;

    //2D textures
    int ATLAS2D = 0;
    int NAME2D = 1;

    //level
    World* theWorld;

    //General data
    std::vector<unsigned int> allVAOs;
    std::vector<unsigned int> allVBOs;
    std::vector<Shader*> allShaders;
    std::vector<Texture*> allTextures;
    std::vector<AssimpModel*> allModels;
    std::vector<glm::vec3*> lightPositions;

    //enemy data
    std::vector<Enemy* > allEnemies;
    std::vector<Bullet*> enemyBullets;
    int enemyAmount = 0;
    float enemyCounter = 3.0;
    int enemyLimit = 10;
    int enemieSpawned = 0;
    int enemiesPerLevel[5] = {20,25,30,40,50};
    //player data
    Player* daPlayer;

    //Base function

    glm::mat4 getPerspective(float halfAngle,float aspect, float closeP, float farP);

    unsigned int loadCubText(std::vector<std::string> faces);

    void bulletUpdate(std::vector<Bullet*>& playerBulletArr,std::vector<Bullet*>& enemyBulletArr, glm::vec2 blockSize,std::vector<levelObject*> levelObjects);

//window setup

    static void frameBufferRez(GLFWwindow *window, int fbW, int fbH)
    {
        glViewport(0,0, fbW, fbH);
    }

    static void scrollInput(GLFWwindow* window, double xSet, double ySet)
    {
        //mainCamera.scrollCall(ySet);
    }

    void setGLFW(const char* windwName, const int width, const int height, const int majorVersion, const int minorVersion);

    void enableModes();

    //void setShadowMaps();

    void setEnvironment();

    void updateUniforms();

    void updateTime();

    void updateViewport();

    void refreshGame();

public:

    Game(const char* title,
         const int windowW, const int windowH,
         const int glMajor, const int glMinor);
    ~Game();

    int setTexture2D(const char*);

    void setSkyBoxTexture(const char*, const char*, const char*, const char*, const char*, const char*);

    int setShader(const char*, const char*, int=0, const char* = "");

    void setModel(const char*);

    void initRenderer(const char*, const char*, const char*);

    void setVAOs();

    void setUniforms();

    void setScreen();

    void setupPlayer();

    void setDefaultShaderValues();

    void setLevelData();

    void mouseInput();

    void keyboardInput();

    void update();

    void renderBegin();

    void renderEnd();

    void renderMenu();

    void generalGameUpdate();

    void updateWorld();

    void updatePlayer();

    void updateEnemies();

    void render();

    void renderBackground();

    void renderScreenText();

    void renderScreen();

    void renderScreenAdditions();

    void renderGame();

    void setBasicProgram(int);
    void setBasic2DProgram(int);
    void setCubeTextureProgram(int);
    void setModelProgram(int);
    void setScreenProgram(int);

    void setAtlasTextureNum(int);
    void setGameNameTextureNum(int);
};
#endif
