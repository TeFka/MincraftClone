#ifndef CHUNK_H_INCLUDED
#define CHUNK_H_INCLUDED

#include "../../Util/Array2D.h"
#include "../../Util/NonCopyable.h"
#include "ChunkSection.h"
#include <vector>

class RenderMaster;
class Camera;
class TerrainGenerator;

/// @brief A chunk, in other words, a large arrangement of blocks.
class Chunk : public IChunk {
  public:
    Chunk() = default;
    Chunk(World &world, const glm::ivec2 &location);

    bool makeMesh(const Camera &camera);

    void setBlock(int x, int y, int z, ChunkBlock block) override;
    ChunkBlock getBlock(int x, int y, int z) const noexcept override;
    int getHeightAt(int x, int z);

    void drawChunks(RenderMaster &renderer, const Camera &camera);

    bool hasLoaded() const noexcept;
    void load(TerrainGenerator &generator);

    ChunkSection &getSection(int index);

    const glm::ivec2 &getLocation() const
    {
        return m_location;
    }

    void deleteMeshes();

  private:
    void addSection();
    void addSectionsBlockTarget(int blockY);
    void addSectionsIndexTarget(int index);

    bool outOfBound(int x, int y, int z) const noexcept;

    std::vector<ChunkSection> m_chunks;
    Array2D<int, CHUNK_SIZE> m_highestBlocks;
    glm::ivec2 m_location;

    World *m_pWorld;

    bool m_isLoaded = false;
};

#endif // CHUNK_H_INCLUDED
