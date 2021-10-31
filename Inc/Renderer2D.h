#ifndef RENDERER2D_H_INCLUDED
#define RENDERER2D_H_INCLUDED

#include"struct.h"
#include"Shader.h"
#include"Texture.h"

struct vertex2D
{
    glm::vec2 pos;
    glm::vec2 textr;
    glm::vec4 col;
    int textNr;
};

class Renderer2D{

private:
    Shader* charProg;
    float windowWidth;
    float windowHeight;
    unsigned int basicVAO, basicVBO;
    unsigned int transVAO, transVBO;
    unsigned int textVAO, textVBO;

    std::map<char, Character> characters;

    std::vector<vertex2D> basicVertices;
    std::vector<Texture*> textures;
    int textureAmount = 0;
    std::vector<vertex2D> transparentVertices;

    void setupText(const char*);
    void updateBasicVAO();
    void updateTransVAO();
public:
    Renderer2D();
    void init(const char*, const char*, const char*);

    void update(int, int);

    void writeText(std::string, GLfloat, GLfloat,GLfloat,glm::vec3);
    void setTexture(Texture*);
    void setBasicSprite(float, float, float, float, glm::vec4, int,float=0.0,float=1.0);
    void setTransparentSprite(float, float, float, float, glm::vec4, int,float=0.0,float=1.0);
    void clearVerts();
    void drawBasic(Shader*);
    void drawTransparent(Shader*);
    void render2D(Shader*);

};

#endif // RENDERER2D_H_INCLUDED
