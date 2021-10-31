#ifndef CHUNKSECTION_H_INCLUDED
#define CHUNKSECTION_H_INCLUDED

#include"struct.h"
#include"BlockData.h"

class Layer
{
public:
    void update(int c)
    {
        if (c==0)
        {
            solidBlockCount--;
        }
        else
        {
            solidBlockCount++;
        }
    }

    bool isAllSolid()
    {
        return solidBlockCount == CHUNK_AREA;
    }
    void fillSolid(){
        solidBlockCount = CHUNK_AREA;
    }

private:
    int solidBlockCount = 0;
};

class World;

class ChunkSection
{
    friend class Chunk;
private:

    std::array<int, CHUNK_VOLUME> blocks;
    std::array<Layer, CHUNK_AREA> layers;

    glm::ivec3 location;

    World *theWorld;

    bool outOfBounds(int);
    glm::ivec3 toWorldPosition(int, int, int);
    int getIndex(int, int, int);
public:
    ChunkSection(glm::ivec3, World *);

    void setBlock(int, int, int, int);

    int getBlock(int, int, int);

    glm::ivec3 getLocation();

    void addBlockMesh(std::vector<basicVertex>&, int, int *);

    ChunkSection &getAdjacent(int, int);

    void makeMesh(ChunkMeshCollection*, int *, int*);

    Layer &getLayer(int);

    bool shouldMakeLayer(int y);

    int *begin()
    {
        return &blocks[0];
    }
};

#endif
