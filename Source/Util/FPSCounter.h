#ifndef FPSCOUNTER_H_INCLUDED
#define FPSCOUNTER_H_INCLUDED

#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>

#include "../Text.h"

#include<string.h>

class RenderMaster;

/// @brief Generally obsolete FPS counter associated with SFML.
class FPSCounter {
  public:
    FPSCounter();

    void update();

    void draw(RenderMaster &renderer);

  private:
    bool enabled = false;
    bool debugging;

    Text m_text;

    double previousTime;

    float m_fps = 0;

    int m_frameCount = 0;
};

#endif // FPSCOUNTER_H_INCLUDED
