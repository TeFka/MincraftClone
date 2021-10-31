#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED

#include"struct.h"

class Shader
{
    //members
    std::string loadShaderSource(char*) const;

    GLuint loadShader(GLenum, char*) const;

    void linkProgram(GLuint, GLuint, GLuint);
public:
    GLuint id;
    //contstructor
    Shader(const char*, const char*, const char* = "",int=0);
    ~Shader();
    void use();
    void unUse();
    void set1i(const GLint&, const GLchar*);
    void set1f(const GLfloat&, const GLchar*);
    void setVec2f(const glm::fvec2&, const GLchar*);
    void setVec3f(const glm::fvec3&, const GLchar*);
    void setVec4f(const glm::fvec4&, const GLchar*);
    void setMat3(const glm::mat3 &, const GLchar*, GLboolean=GL_FALSE);
    void setMat4(const glm::mat4 &, const GLchar*, GLboolean=GL_FALSE);
    void setUb(const GLchar*,GLuint);
};
#endif
