#include "WaterShader.h"

WaterShader::WaterShader()
    : BasicShader("Water", "Chunk")
{
    std::cout<<"WaterShaderDebug1"<<std::endl;
    getUniforms();
    std::cout<<"WaterShaderDebug2"<<std::endl;
}

void WaterShader::loadTime(const float &time)
{
    loadFloat(m_time, time);
}

void WaterShader::getUniforms()
{
    BasicShader::getUniforms();
    m_time = glGetUniformLocation(m_id, "globalTime");
}
