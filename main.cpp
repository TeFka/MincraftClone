
#include<gameClass.h>

#include <iostream>

#include "Inc/helpers/RootDir.h"

using namespace std;

int main()
{
    cout<<"declare1"<<endl;
    Game daGam("Game1",1000,800,4,4);
    cout<<"declare2"<<endl;
    //resource data
    string rootDir = ROOT_DIR;

    //shaders
    string shaderDir = "Resources/shaders/";
    string shaderNames[12] = {"basic_vert.glsl", "basic_frag.glsl",
                              "model_vert.glsl", "model_frag.glsl",
                              "cubeText_vert.glsl","cubeText_frag.glsl",
                              "basic2D_vert.glsl","basic2D_frag.glsl",
                              "text_vert.glsl","text_frag.glsl",
                              "screen_vert.glsl", "screen_frag.glsl"
                             };

    daGam.setBasicProgram( daGam.setShader((ROOT_DIR+shaderDir+shaderNames[0]).c_str(),(ROOT_DIR+shaderDir+shaderNames[1]).c_str(),0));
    daGam.setBasic2DProgram(daGam.setShader((ROOT_DIR+shaderDir+shaderNames[6]).c_str(),(ROOT_DIR+shaderDir+shaderNames[7]).c_str(),0));
    daGam.setCubeTextureProgram(daGam.setShader((ROOT_DIR+shaderDir+shaderNames[4]).c_str(),(ROOT_DIR+shaderDir+shaderNames[5]).c_str(),0));
    daGam.setModelProgram(daGam.setShader((ROOT_DIR+shaderDir+shaderNames[2]).c_str(),(ROOT_DIR+shaderDir+shaderNames[3]).c_str(),0));
    daGam.setScreenProgram(daGam.setShader((ROOT_DIR+shaderDir+shaderNames[10]).c_str(),(ROOT_DIR+shaderDir+shaderNames[11]).c_str(),0));

    //textures
    string textureDir = "Resources/textures/";
    string textureNames[8] = {"left.jpg",
                              "right.jpg",
                              "top.jpg",
                              "bottom.jpg",
                              "front.jpg",
                              "back.jpg",
                              "atlas.jpg", "name.png"
                             };

    daGam.setAtlasTextureNum(daGam.setTexture2D((ROOT_DIR+textureDir+textureNames[6]).c_str()));
    daGam.setGameNameTextureNum(daGam.setTexture2D((ROOT_DIR+textureDir+textureNames[7]).c_str()));

    daGam.setSkyBoxTexture((ROOT_DIR+textureDir+textureNames[0]).c_str(),
                           (ROOT_DIR+textureDir+textureNames[1]).c_str(),
                           (ROOT_DIR+textureDir+textureNames[2]).c_str(),
                           (ROOT_DIR+textureDir+textureNames[3]).c_str(),
                           (ROOT_DIR+textureDir+textureNames[4]).c_str(),
                           (ROOT_DIR+textureDir+textureNames[5]).c_str());

    //models
    string modelsDir = "Resources/models/";
    string modelNames[1] = {"guy.dae"};

    daGam.setModel((ROOT_DIR+modelsDir+modelNames[0]).c_str());
    //setup
    daGam.initRenderer("C:/Windows/Fonts/arial.ttf",
                       (ROOT_DIR+shaderDir+shaderNames[8]).c_str(),(ROOT_DIR+shaderDir+shaderNames[9]).c_str());

    daGam.setVAOs();
    daGam.setUniforms();
    daGam.setDefaultShaderValues();
    daGam.setLevelData();
    daGam.setScreen();
    daGam.setupPlayer();

    while(1)
    {

        daGam.renderGame();
    }

    delete &daGam;
    return 0;
}

