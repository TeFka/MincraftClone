#ifndef RENDERMASTER_H_INCLUDED
#define RENDERMASTER_H_INCLUDED

#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>

#include "../Config.h"
#include "ChunkRenderer.h"
#include "FloraRenderer.h"
#include "SkyboxRenderer.h"
#include "WaterRenderer.h"
#include "TextRenderer.h"

class Camera;
class ChunkSection;

/// @brief Master rendering class that handles the sum of drawn in-game objects.
class RenderMaster {
  public:

    RenderMaster();
    RenderMaster(GLFWwindow* theWindow);

    void drawChunk(const ChunkSection &chunk);
    void drawSky();
    void addText(Text*);

    void finishRender(GLFWwindow* window, const Camera &camera);

    GLFWwindow* getWindow();
    void setWindow(GLFWwindow*);
    
  private:
    // Chunks
    ChunkRenderer m_chunkRenderer;
    WaterRenderer m_waterRenderer;
    FloraRenderer m_floraRenderer;
    TextRenderer m_textRenderer;

    // Detail
    SkyboxRenderer m_skyboxRenderer;

    bool m_drawBox = false;

    GLFWwindow* mainWindow;
};

#endif // RENDERMASTER_H_INCLUDED
