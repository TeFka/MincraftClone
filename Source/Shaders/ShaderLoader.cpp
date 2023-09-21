#include "ShaderLoader.h"

#include "../Util/FileUtil.h"

#include <glad/glad.h>

#include <stdexcept>

namespace {
GLuint compileShader(const GLchar *source, GLenum shaderType)
{
    std::cout<<"ShaderCompileDebug1"<<std::endl;
    GLuint shaderID = glCreateShader(shaderType);
    std::cout<<"ShaderCompileDebug2"<<std::endl;
    glShaderSource(shaderID, 1, &source, nullptr);
    glCompileShader(shaderID);
    std::cout<<"ShaderCompileDebug3"<<std::endl;
    GLint isSuccess = 0;
    GLchar infoLog[512];
    std::cout<<"ShaderCompileDebug4"<<std::endl;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isSuccess);
    if (!isSuccess) {
        glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
        throw std::runtime_error("Unable to load a shader: " + std::string(infoLog));
    }
    std::cout<<"ShaderCompileDebug5"<<std::endl;
    return shaderID;
}

GLuint linkProgram(GLuint vertexShaderID, GLuint fragmentShaderID)
{
    auto id = glCreateProgram();

    glAttachShader(id, vertexShaderID);
    glAttachShader(id, fragmentShaderID);

    glLinkProgram(id);

    return id;
}
} // namespace

GLuint loadShaders(const std::string &vertexShader,
                   const std::string &fragmentShader)
{
    std::cout<<"ShaderLoaderDebug1"<<std::endl;
    auto vertexSource = getFileContents("../Shaders/" + vertexShader + ".vert");
    auto fragmentSource = getFileContents("../Shaders/" + fragmentShader + ".frag");
    std::cout<<"ShaderLoaderDebug2"<<std::endl;
    auto vertexShaderID = compileShader(vertexSource.c_str(), GL_VERTEX_SHADER);
    auto fragmentShaderID = compileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);
    std::cout<<"ShaderLoaderDebug3"<<std::endl;
    auto shaderID = linkProgram(vertexShaderID, fragmentShaderID);
    std::cout<<"ShaderLoaderDebug4"<<std::endl;
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    std::cout<<"ShaderLoaderDebug5"<<std::endl;

    return shaderID;
}
