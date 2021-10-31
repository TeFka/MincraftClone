#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <functional>
#include <memory>
#include <unordered_map>

#include"struct.h"
#include"BlockData.h"
#include"Shader.h"
#include"Texture.h"
#include"WorldGenerator.h"
#include"Chunk.h"

class World
{
private:

    int updating = 1;
    std::vector<std::thread> updateThreads;
    int completed;
    int change = 0;

    Texture* texture;

    int loadDistance = 10;

    WorldGenerator worldGenerator;

    float blockSize;
    std::vector<levelObject*> activeBlocks;
    int blockUpdate = 0;

    int currentChunk;
    int chunkUpdate = 0;

    glm::vec3 playerPos;

    std::unordered_map<VectorXZ, Chunk> activeChunks;
    std::vector<VectorXZ> chunksToGenerate;
    std::vector<VectorXZ> chunksToUpdate;
    int activeChunksNum;

    ChunkMeshCollection vertices;
    int tempVerticesCount = 0;
    int verticesNr = 0;
    int allVerticesNr = 0;

    int maxHeight = 100;

    float movementCounter = 1.0;

    unsigned int VAO, VBO;
    unsigned int trnVAO, trnVBO;

    float globalBias = 1.3;

    void updateVAO();

    void deleteChunk(int, int);

    void initChunk(int, int);

    void loadChunks(glm::vec3);

   // void updateChunk(int, int, int);

    //void initActiveBlocks();

    void blockChangeUpdate(int);

public:
    BlockDatabase bDatabase;

    World(Texture*,glm::vec3&);

    ~World();

    glm::vec3 setSpawn();

    int getBlockCount();
    std::vector<levelObject*> getBlocks();
    float getBlockSize();
    VectorXZ getBlockXZ(int, int);
    VectorXZ getChunkXZ(int, int);

    //chunk control
    Chunk& getChunk(int, int);

    int getBlock(int, int, int);

    void setBlock(int, int, int, int);

    void deleteChunkMesh(int, int);

    //void setDestroyedBlock(int,int,int,int,int);

    void update(glm::vec3&,float);

    void drawMesh(Shader*);
};

#endif
