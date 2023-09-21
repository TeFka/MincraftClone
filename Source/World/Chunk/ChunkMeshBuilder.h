#ifndef CHUNKMESHBUILDER_H_INCLUDED
#define CHUNKMESHBUILDER_H_INCLUDED

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>
#include <vector>

#include<array>

#include"../../Maths/glm.h"

#include "../Block/ChunkBlock.h"

class ChunkSection;
class ChunkMesh;
class BlockData;

struct ChunkMeshCollection;
struct BlockDataHolder;

class ChunkMeshBuilder {
  public:
    ChunkMeshBuilder(ChunkSection &chunk, ChunkMeshCollection &meshes);

    void buildMesh();

  private:
    void setActiveMesh(ChunkBlock block);

    void addXBlockToMesh(const glm::ivec2 &textureCoords,
                         const glm::ivec3 &blockPosition);

    void tryAddFaceToMesh(const std::array<GLfloat, 12> &blockFace,
                          const glm::ivec2 &textureCoords,
                          const glm::ivec3 &blockPosition,
                          const glm::ivec3 &blockFacing,
                          GLfloat cardinalLight);

    bool shouldMakeFace(const glm::ivec3 &blockPosition,
                        const BlockDataHolder &blockData);

    bool shouldMakeLayer(int y);

    const ChunkBlock *m_pBlockPtr = nullptr;
    ChunkSection *m_pChunk = nullptr;
    ChunkMeshCollection *m_pMeshes = nullptr;
    ChunkMesh *m_pActiveMesh = nullptr;
    const BlockDataHolder *m_pBlockData = nullptr;
};

#endif // CHUNKMESHBUILDER_H_INCLUDED
