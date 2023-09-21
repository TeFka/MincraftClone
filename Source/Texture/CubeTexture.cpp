#include "CubeTexture.h"

CubeTexture::CubeTexture(const std::array<std::string, 6> &files)
{
    std::cout<<"CubeTextureDebug1"<<std::endl;
    loadFromFiles(files);
    std::cout<<"CubeTextureDebug1"<<std::endl;
}

CubeTexture::~CubeTexture()
{
    glDeleteTextures(1, &m_texId);
}

void CubeTexture::loadFromFiles(const std::array<std::string, 6> &files)
{
    std::cout<<"SkyboxTextureLoadDebug1"<<std::endl;
    glGenTextures(1, &m_texId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texId);
    std::cout<<"SkyboxTextureLoadDebug2"<<std::endl;
    for (int i = 0; i < 6; i++) {

        auto &str = files[i];
        int width, height, nrChannels;
        std::cout<<"SkyboxTextureLoadDebug21: "<<str<<std::endl;
        unsigned char *data = stbi_load(("../Res/Textures/" + str + ".png").c_str(),&width,&height,  &nrChannels, 0);
        std::cout<<"SkyboxTextureLoadDebug22: "<<str<<std::endl;
        if (data) {
            auto param = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;

            glTexImage2D(param, 0, GL_RGBA, width, height, 0, GL_RGB,
                        GL_UNSIGNED_BYTE, data);
        }
        else {
            throw std::runtime_error("Unable to load CubeTexture Part: " + str);
        }
        std::cout<<"SkyboxTextureLoadDebug23: "<<str<<std::endl;
        stbi_image_free(data);
        std::cout<<"SkyboxTextureLoadDebug24: "<<str<<std::endl;
    }
    std::cout<<"SkyboxTextureLoadDebug3"<<std::endl;
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    std::cout<<"SkyboxTextureLoadDebug4"<<std::endl;
}

void CubeTexture::bindTexture() const
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texId);
}
