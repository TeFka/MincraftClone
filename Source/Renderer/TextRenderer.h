#ifndef TEXTRENDERER_H_INCLUDED
#define TEXTRENDERER_H_INCLUDED

#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>
#include <vector>

#include "../Text.h"
#include "../Shaders/TextShader.h"

struct RenderInfo;
class Camera;

/// @brief Renderer specifically used to render screen text
class TextRenderer {
  public:
    void add(Text* newText);
    void render(GLFWwindow* theWindow, const Camera &camera);

  private:
    std::vector<Text*> words;

    void writeText(GLFWwindow* theWindow, Text*);

    TextShader m_shader;
};

#endif // TEXTRENDERER_H_INCLUDED
