#ifndef CHUNKSECTION_H_INCLUDED
#define CHUNKSECTION_H_INCLUDED

#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>
#include <array>

#include "../Block/ChunkBlock.h"
#include "../WorldConstants.h"
#include "ChunkMesh.h"
#include "IChunk.h"

#include"../../Maths/glm.h"

#include "../../Physics/AABB.h"
#include "../Block/BlockData.h"

class World;

class ChunkSection : public IChunk {
    friend class Chunk;

    class Layer {
      public:
        void update(ChunkBlock c)
        {
            if (c.getData().isOpaque) {
                m_solidBlockCount--;
            }
            else {
                m_solidBlockCount++;
            }
        }

        bool isAllSolid() const
        {
            return m_solidBlockCount == CHUNK_AREA;
        }

      private:
        int m_solidBlockCount = 0;
    };

  public:
    ChunkSection(const glm::ivec3 &position, World &world);

    void setBlock(int x, int y, int z, ChunkBlock block) override;
    ChunkBlock getBlock(int x, int y, int z) const override;

    const glm::ivec3 getLocation() const;

    bool hasMesh() const;
    bool hasBuffered() const;

    void makeMesh();
    void bufferMesh();

    const Layer &getLayer(int y) const;
    ChunkSection &getAdjacent(int dx, int dz);

    const ChunkMeshCollection &getMeshes() const
    {
        return m_meshes;
    }

    void deleteMeshes();

    const ChunkBlock *begin()
    {
        return &m_blocks[0];
    }

  private:
    glm::ivec3 toWorldPosition(int x, int y, int z) const;

    static bool outOfBounds(int value);
    static int getIndex(int x, int y, int z);

    std::array<ChunkBlock, CHUNK_VOLUME> m_blocks;
    std::array<Layer, CHUNK_SIZE> m_layers;

    ChunkMeshCollection m_meshes;
    AABB m_aabb;
    glm::ivec3 m_location;

    World *m_pWorld;

    bool m_hasMesh = false;
    bool m_hasBufferedMesh = false;
};

#endif // CHUNKSECTION_H_INCLUDED
