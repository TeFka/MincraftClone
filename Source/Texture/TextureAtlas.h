#ifndef TEXTUREATLAS_H_INCLUDED
#define TEXTUREATLAS_H_INCLUDED

#include <stdexcept>

#include <array>

#include "BasicTexture.h"

#include "../../Support/stb_image.h"
#include "../Maths/glm.h"

/// @brief Texture atlas that pulls texture data from existing files and maps them appropraitely.
class TextureAtlas : public BasicTexture {
  public:
    TextureAtlas(const std::string &textureFileName);

    std::array<GLfloat, 8> getTexture(const glm::ivec2 &coords);

  private:
    int m_imageSize;
    int m_individualTextureSize;
};

#endif // TEXTUREATLAS_H_INCLUDED
