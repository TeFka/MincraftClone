#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include"struct.h"

class Texture
{
private:
    GLuint id;
    int height;
    int width;
    unsigned int type;
    std::string typ;
    const char* path;
    GLint textureUnit;
public:
    Texture(const char*,GLenum,GLint,std::string="texture_diffuse");
    ~Texture();
    GLuint getId();

    std::string getTyp();

    const char* getPath();

    void bindT();

    void unBindT();

    GLuint getUnit();

    void loadNewTex(const char*,GLenum);

};
#endif
