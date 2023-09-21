#include "RenderMaster.h"

#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>
#include <iostream>

#include "../Application.h"
#include "../Context.h"
#include "../World/Chunk/ChunkMesh.h"
#include "../World/Chunk/ChunkSection.h"

RenderMaster::RenderMaster(){


    
}

RenderMaster::RenderMaster(GLFWwindow* theWindow){

    mainWindow = theWindow;

}
void RenderMaster::drawChunk(const ChunkSection &chunk)
{
    const auto &solidMesh = chunk.getMeshes().solidMesh;
    const auto &waterMesh = chunk.getMeshes().waterMesh;
    const auto &floraMesh = chunk.getMeshes().floraMesh;

    if (solidMesh.faces > 0)
        m_chunkRenderer.add(solidMesh);

    if (waterMesh.faces > 0)
        m_waterRenderer.add(waterMesh);

    if (floraMesh.faces > 0)
        m_floraRenderer.add(floraMesh);
}

void RenderMaster::drawSky()
{
    m_drawBox = true;
}

void RenderMaster::addText(Text* newText){

    m_textRenderer.add(newText);

}

void RenderMaster::finishRender(GLFWwindow* window, const Camera &camera)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    m_chunkRenderer.render(camera);
    m_waterRenderer.render(camera);
    m_floraRenderer.render(camera);

    if (m_drawBox) {
        glDisable(GL_CULL_FACE);
        m_skyboxRenderer.render(camera);
        m_drawBox = false;
    }
    
    m_textRenderer.render(window, camera);

    glfwSwapBuffers(window);
    glFlush();
    glfwPollEvents();
    glBindVertexArray(0);
    glUseProgram(0);
    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);

}

GLFWwindow* RenderMaster::getWindow(){

    return mainWindow;

}

void RenderMaster::setWindow(GLFWwindow* newWindow){

    mainWindow = newWindow;

}
