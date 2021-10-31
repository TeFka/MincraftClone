#ifndef CHUNK_H_INCLUDED
#define CHUNK_H_INCLUDED

#include"struct.h"
#include"ChunkSection.h"
#include"ChunkMap.h"
#include"BlockData.h"

class WorldGenerator;

class Chunk
{
private:
    int groundVertStart=0;
    int groundVertNr=0;
    int waterVertStart=0;
    int waterVertNr=0;

    std::vector<ChunkSection> chunks;
    std::array<int, CHUNK_AREA> highestBlocks;
    glm::ivec2 location;

    ChunkMeshCollection* meshes;

    World *theWorld;

    bool isLoaded = false;
    bool hasMesh = false;
    void addSection();
    void addSectionsBlockTarget(int);
    void addSectionsIndexTarget(int);

public:
    Chunk() = default;
    Chunk(World *, ChunkMeshCollection*,int, int);

    bool outOfBound(int x, int y, int z);

    bool makeMesh();

    void setBlock(int, int, int, int);
    int getBlock(int, int, int);

    int getHeightAt(int, int);

    bool hasLoaded();

    void load(WorldGenerator&);

    ChunkSection &getSection(int);

    glm::ivec2 &getLocation();

    bool deleteMeshes();

    void refreshMeshValues();

    int getGroundVertStart();

    int getGroundVertNr();

    int getWaterVertStart();

    int getWaterVertNr();

    void setGroundVertStart(int);

    void setWaterVertStart(int);
};
#endif
