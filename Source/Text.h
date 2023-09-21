#ifndef TEXTMANAGER_H_INCLUDED
#define TEXTMANAGER_H_INCLUDED

#pragma once

#include<iostream>

#include<glad/glad.h>
#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>

#include <vector>
#include <map>

#include<glm.hpp>
#include<vec3.hpp>

#include<ft2build.h>
#include FT_FREETYPE_H

#include"./Renderer/RenderInfo.h"
#include"./Model.h"

struct Character
{
    GLuint text;
    glm::ivec2 siz;
    glm::ivec2 bear;
    GLuint advance;
};

class Text{

private:

public:
    
    Model renderData;
    GLuint textVBO;

    std::map<char, Character> characters;

    glm::vec2 position;
    int scale;
    glm::vec4 color;

    std::string textValue;

    Text();
    Text(std::string);
    ~Text();

    float checkTextLength(std::string, float);
    float checkTextMaxHeight(std::string, float);

    void setTextFont(std::string);

    void setTextValue(std::string);

    void setPosition(glm::vec2);
    void setScale(int);
    void setColor(glm::vec4);
};

#endif // TEXTMANAGER_H_INCLUDED
