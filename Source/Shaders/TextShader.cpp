#include "TextShader.h"

TextShader::TextShader()
    : BasicShader("Text", "Chunk")
{
    std::cout<<"TextShaderDebug1"<<std::endl;
    getUniforms();
    std::cout<<"TextShaderDebug2"<<std::endl;
}

void TextShader::loadTime(const float &time)
{
    loadFloat(m_time, time);
}

void TextShader::loadTextColor(glm::vec3 newCol)
{
    loadVector3(textColor, newCol);
}

void TextShader::getUniforms()
{
    BasicShader::getUniforms();
    m_time = glGetUniformLocation(m_id, "globalTime");
    textColor = glGetUniformLocation(m_id, "textCol");
}
