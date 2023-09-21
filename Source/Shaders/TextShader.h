#ifndef TEXTSHADER_H_INCLUDED
#define TEXTSHADER_H_INCLUDED

#include "BasicShader.h"

/// @brief Shader affecting screen text
class TextShader : public BasicShader {
  public:
    TextShader();
    void loadTime(const float &time);

    void loadTextColor(glm::vec3);

  private:
    void getUniforms() override;
    GLuint m_time;
    GLuint textColor;
};

#endif // TEXTSHADER_H_INCLUDED
