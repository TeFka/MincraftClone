#include "FloraShader.h"

FloraShader::FloraShader()
    : BasicShader("Flora", "Chunk")
{
    std::cout<<"FloraShaderDebug1"<<std::endl;
    getUniforms();
    std::cout<<"FloraShaderDebug2"<<std::endl;
}

void FloraShader::loadTime(const float &time)
{
    loadFloat(m_time, time);
}

void FloraShader::getUniforms()
{
    BasicShader::getUniforms();
    m_time = glGetUniformLocation(m_id, "globalTime");
}
