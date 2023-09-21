#include "ChunkShader.h"

ChunkShader::ChunkShader()
    : BasicShader("Chunk", "Chunk")
{
    std::cout<<"ChunkShaderDebug1"<<std::endl;
    getUniforms();
    std::cout<<"ChunkShaderDebug2"<<std::endl;
}

void ChunkShader::getUniforms()
{
    BasicShader::getUniforms();
}
