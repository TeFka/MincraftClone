#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>
#include <vector>

/// @brief Mesh struct used for the purpose of constructing block meshes.
struct Mesh {
    std::vector<GLfloat> vertexPositions;
    std::vector<GLfloat> textureCoords;
    std::vector<GLuint> indices;
};

#endif // MESH_H_INCLUDED
