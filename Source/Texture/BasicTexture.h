#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <stdexcept>

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>
#include <string>

#include "../../Support/stb_image.h"

#include "../Util/NonCopyable.h"

/// @brief Standard texture that will be mapped to objects.
class BasicTexture : public NonCopyable {
  public:
    BasicTexture() = default;
    BasicTexture(const std::string &file);

    ~BasicTexture();

    void loadFromImage(unsigned char *textrPointr);
    void loadFromFile(const std::string &file);

    void bindTexture() const;

  protected:
    GLuint m_id;
    int width;
    int height;
};

#endif // TEXTURE_H_INCLUDED
