#include "TextRenderer.h"

#include "../Camera.h"

#include <iostream>

#include "../Application.h"

void TextRenderer::add(Text* newText){

    words.push_back(newText);

}


void TextRenderer::render(GLFWwindow* theWindow, const Camera &camera)
{

    glEnable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    m_shader.useProgram();

    m_shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix());
    m_shader.loadTime(g_timeElapsed);

    for (auto word : words) {

        GL::bindVAO(word->renderData.getRenderInfo().vao);

        writeText(theWindow, word);

        GL::drawElements(word->renderData.getRenderInfo().indicesCount);

    }

    words.clear();

}

void TextRenderer::writeText(GLFWwindow* theWindow, Text* word)
{   

    int width, height;
    glfwGetWindowSize(theWindow, &width, &height);

    GLfloat x = float(width)*word->position.x;
    GLfloat y = float(height)*word->position.y;

    glEnable(GL_BLEND);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);

    m_shader.loadTextColor(word->color);

    glActiveTexture(GL_TEXTURE0);
    
    std::string::const_iterator c;
    GLfloat sum = 0;

    for(c=word->textValue.begin(); c!=word->textValue.end(); c++)
    {
        Character ch = word->characters[*c];
        sum+=(ch.advance >> 6) * word->scale;
    }

    x=x-sum/2;

    for(c=word->textValue.begin(); c!=word->textValue.end(); c++)
    {
        Character ch = word->characters[*c];
        GLfloat xPos = x+ch.bear.x*word->scale;
        GLfloat yPos = y-((ch.siz.y-ch.bear.y)*word->scale);
        GLfloat chW = ch.siz.x*word->scale;
        GLfloat chH = ch.siz.y*word->scale;
        GLfloat chVertices[6][4]=
        {
            {xPos,yPos+chH,0.0,0.0},
            {xPos,yPos,0.0,1.0},
            {xPos+chW,yPos,1.0,1.0},
            {xPos,yPos+chH,0.0,0.0},
            {xPos+chW,yPos,1.0,1.0},
            {xPos+chW,yPos+chH,1.0,0.0}
        };
        glBindTexture(GL_TEXTURE_2D,ch.text);
        glBindBuffer(GL_ARRAY_BUFFER,word->textVBO);
        glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(chVertices),chVertices);
        glDrawArrays(GL_TRIANGLES,0,6);
        x += (ch.advance >> 6) * word->scale;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D,0);
    glDisable(GL_BLEND);
    
}

