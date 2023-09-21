#ifndef CHUNKMESH_H_INCLUDED
#define CHUNKMESH_H_INCLUDED

#include "../../Model.h"

#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>
#include <array>
#include <vector>

#include"../../Maths/glm.h"

class ChunkMesh {
  public:
    ChunkMesh() = default;

    void addFace(const std::array<GLfloat, 12> &blockFace,
                 const std::array<GLfloat, 8> &textureCoords,
                 const glm::ivec3 &chunkPosition,
                 const glm::ivec3 &blockPosition, GLfloat cardinalLight);

    void bufferMesh();

    const Model &getModel() const;

    void deleteData();

    int faces = 0;

  private:
    Mesh m_mesh;
    Model m_model;
    std::vector<GLfloat> m_light;
    GLuint m_indexIndex = 0;
};

struct ChunkMeshCollection {
    ChunkMesh solidMesh;
    ChunkMesh waterMesh;
    ChunkMesh floraMesh;
};

#endif // CHUNKMESH_H_INCLUDED
