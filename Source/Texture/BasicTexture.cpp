#include "BasicTexture.h"

BasicTexture::BasicTexture(const std::string &file)
{
    loadFromFile(file);
}

void BasicTexture::loadFromImage(unsigned char *textrPointr)
{
    glGenTextures(1, &m_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, textrPointr);

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1);
}
void BasicTexture::loadFromFile(const std::string &file)
{   
    int nrChannels;
    unsigned char *data = stbi_load(("../Res/Textures/" + file + ".png").c_str(),&width,&height,  &nrChannels, 0);
    if (data) {
        loadFromImage(data);   
    }
    else{
        throw std::runtime_error("Unable to open image: " + file);
    }

    loadFromImage(data);
}

BasicTexture::~BasicTexture()
{
    glDeleteTextures(1, &m_id);
}

void BasicTexture::bindTexture() const
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}
