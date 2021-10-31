#include "../Inc/Chunk.h"
#include "../Inc/WorldGenerator.h"

Chunk::Chunk(World *world, ChunkMeshCollection* meshs, int x, int z)
{
    this->location.x = x;
    this->location.y = z;
    this->theWorld = world;
    this->highestBlocks.fill(0);
    this->meshes = meshs;
    //std::cout<<"make chunk: "<<x<<"  "<<z<<std::endl;
}

void Chunk::addSection()
{
    int y = chunks.size();
    chunks.emplace_back(glm::ivec3(location.x, y, location.y),this->theWorld);
}
void Chunk::addSectionsBlockTarget(int blockY)
{
    int index = blockY / CHUNK_SIZE;
    addSectionsIndexTarget(index);
}
void Chunk::addSectionsIndexTarget(int index)
{
    while ((int)chunks.size() < index + 1)
    {
        addSection();
    }
}

bool Chunk::outOfBound(int x, int y, int z)
{
    if (x >= CHUNK_SIZE)
        return true;
    if (z >= CHUNK_SIZE)
        return true;

    if (x < 0)
        return true;
    if (y < 0)
        return true;
    if (z < 0)
        return true;

    if (y >= (int)chunks.size() * CHUNK_SIZE)
    {
        return true;
    }

    return false;
}

bool Chunk::makeMesh()
{
    if (!this->hasMesh)
    {
        this->groundVertStart = this->meshes->solidMesh.size();
        this->waterVertStart = this->meshes->waterMesh.size();
        //std::cout<<"making mesh"<<std::endl;
        for (auto &chunk : chunks)
        {
            chunk.makeMesh(this->meshes, &this->groundVertNr,&this->waterVertNr);
        }
        //std::cout<<"made mesh"<<std::endl;
        this->hasMesh = true;
        return true;
    }
    return false;
}

void Chunk::setBlock(int x, int y, int z, int blockId)
{
    addSectionsBlockTarget(y);
    if (outOfBound(x, y, z))
        return;
    int bY = y % CHUNK_SIZE;
    chunks[y / CHUNK_SIZE].setBlock(x, bY, z, blockId);
    if (y == highestBlocks[x*CHUNK_SIZE+z])
    {
        auto highBlock = getBlock(x, y--, z);
        /*while (!highBlock.topTexture==0)
        {
            highBlock = getBlock(x, y--, z);
        }*/
    }
    else if (y > highestBlocks[x*CHUNK_SIZE+z])
    {
        highestBlocks[x*CHUNK_SIZE+z] = y;
    }
    if (isLoaded)
    {
        // m_pWorld->updateChunk(x, y, z);
    }
}
int Chunk::getBlock(int x, int y, int z)
{
    if (outOfBound(x, y, z))
    {
        //std::cout<<"chunk: "<<this->location.x<<"  "<<this->location.y<<std::endl;
        //std::cout<<"outBlock: "<<x<<"  "<<y<<"  "<<z<<std::endl;
        return 0;
    }
    int bY = y % CHUNK_SIZE;
    return chunks[y / CHUNK_SIZE].getBlock(x, bY, z);
}

int Chunk::getHeightAt(int x, int z)
{
    return highestBlocks[x*CHUNK_SIZE+z];
}

bool Chunk::hasLoaded()
{
    return this->isLoaded;
}

void Chunk::load(WorldGenerator& generator)
{
    if (!this->hasLoaded())
    {
        //std::cout<<"loeading chunk"<<std::endl;
        generator.generateTerrainFor(*this);
        //flat test
        /*for (int x = 0; x < CHUNK_SIZE; x++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                this->setBlock(x, 0, z, {4,4});
                this->setBlock(x, 1, z, {2,2});
                this->setBlock(x, 2, z, {2,2});
                this->setBlock(x, 3, z, {2,2});
                this->setBlock(x, 4, z, {1,3});
            }
        }*/
        //std::cout<<"loaded"<<std::endl;
        this->isLoaded = true;
    }
}

ChunkSection &Chunk::getSection(int index)
{
    return chunks[index];
}

glm::ivec2 &Chunk::getLocation()
{
    return location;
}

bool Chunk::deleteMeshes()
{
    if(this->hasMesh)
    {
        this->meshes->solidMesh.erase(this->meshes->solidMesh.begin()+this->groundVertStart,
                                      this->meshes->solidMesh.begin()+this->groundVertStart+this->groundVertNr);
        this->meshes->waterMesh.erase(this->meshes->waterMesh.begin()+this->waterVertStart,
                                      this->meshes->waterMesh.begin()+this->waterVertStart+this->waterVertNr);
    }
    return this->hasMesh;
}

void Chunk::refreshMeshValues()
{
    this->hasMesh = 0;
    this->groundVertNr = 0;
    this->waterVertNr = 0;
}

int Chunk::getGroundVertStart()
{
    return this->groundVertStart;
}

int Chunk::getGroundVertNr()
{
    return this->groundVertNr;
}

int Chunk::getWaterVertStart()
{
    return this->waterVertStart;
}

int Chunk::getWaterVertNr()
{
    return this->waterVertNr;
}

void Chunk::setGroundVertStart(int newStart)
{
    this->groundVertStart = newStart;
}

void Chunk::setWaterVertStart(int newStart)
{
    this->waterVertStart = newStart;
}
