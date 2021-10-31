
#include "../Inc/ChunkSection.h"
#include "../Inc/World.h"

ChunkSection::ChunkSection(glm::ivec3 location, World *world)
{
    this->blocks.fill(0);
    this->theWorld = world;
    this->location = location;
}

bool ChunkSection::outOfBounds(int value)
{
    return (value >= CHUNK_SIZE || value < 0);
}

glm::ivec3 ChunkSection::toWorldPosition(int x, int y, int z)
{
    return glm::vec3(location.x * CHUNK_SIZE + x, location.y * CHUNK_SIZE + y,
                     location.z * CHUNK_SIZE + z);
}

int ChunkSection::getIndex(int x, int y, int z)
{
    return y * CHUNK_AREA + z * CHUNK_SIZE + x;
}

ChunkSection &ChunkSection::getAdjacent(int dx, int dz)
{
    int newX = location.x + dx;
    int newZ = location.z + dz;

    return this->theWorld->getChunk(newX, newZ)
           .getSection(location.y);
}

glm::ivec3 ChunkSection::getLocation()
{
    return location;
}

void ChunkSection::addBlockMesh(std::vector<basicVertex>& vertices, int index, int *vertsCount)
{
    int x = (index % CHUNK_SIZE);
    int y = (index / (CHUNK_AREA));
    int z = ((index / CHUNK_SIZE) % CHUNK_SIZE);
    int tempBlock;
    auto location = toWorldPosition(x, y, z);
    //positiveY
    tempBlock = getBlock(x, y+1, z);
    //std::cout<<"block: "<<tempBlock<<std::endl;
    if(this->theWorld->bDatabase.blockTypes[tempBlock].opacity<1.0f)
    {
        if (tempBlock != this->blocks[index])
        {
            //std::cout<<tempBlock<<"  "<<this->blocks[index]<<std::endl;
            vertices.push_back(basicVertex{glm::vec3(location.x-BLOCK_HALF_SIZE,
                                           location.y+BLOCK_HALF_SIZE,
                                           location.z-BLOCK_HALF_SIZE),
                                           glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].topTextureBegin,1.0),
                                           glm::vec3(0.0,1.0,0.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
            vertices.push_back(basicVertex{glm::vec3(location.x-BLOCK_HALF_SIZE,
                                           location.y+BLOCK_HALF_SIZE,
                                           location.z+BLOCK_HALF_SIZE),
                                           glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].topTextureBegin,0.0),
                                           glm::vec3(0.0,1.0,0.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
            vertices.push_back(basicVertex{glm::vec3(location.x+BLOCK_HALF_SIZE,
                                           location.y+BLOCK_HALF_SIZE,
                                           location.z+BLOCK_HALF_SIZE),
                                           glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].topTextureEnd,0.0),
                                           glm::vec3(0.0,1.0,0.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
            vertices.push_back(basicVertex{glm::vec3(location.x-BLOCK_HALF_SIZE,
                                           location.y+BLOCK_HALF_SIZE,
                                           location.z-BLOCK_HALF_SIZE),
                                           glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].topTextureBegin,1.0),
                                           glm::vec3(0.0,1.0,0.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
            vertices.push_back(basicVertex{glm::vec3(location.x+BLOCK_HALF_SIZE,
                                           location.y+BLOCK_HALF_SIZE,
                                           location.z+BLOCK_HALF_SIZE),
                                           glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].topTextureEnd,0.0),
                                           glm::vec3(0.0,1.0,0.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
            vertices.push_back(basicVertex{glm::vec3(location.x+BLOCK_HALF_SIZE,
                                           location.y+BLOCK_HALF_SIZE,
                                           location.z-BLOCK_HALF_SIZE),
                                           glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].topTextureEnd,1.0),
                                           glm::vec3(0.0,1.0,0.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
            *vertsCount +=6;
        }
    }
    //negativeY
    if((this->location.y != 0) || y != 0)
    {
        tempBlock = getBlock(x, y-1, z);
        if(this->theWorld->bDatabase.blockTypes[tempBlock].opacity<1.0f)
        {
            if (tempBlock!= this->blocks[index])
            {

                vertices.push_back(basicVertex{glm::vec3(location.x-BLOCK_HALF_SIZE,
                                                location.y-BLOCK_HALF_SIZE,
                                                location.z+BLOCK_HALF_SIZE),
                                                glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].bottomTextureBegin,1.0),
                                    glm::vec3(0.0,-1.0,0.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
                 vertices.push_back(basicVertex{glm::vec3(location.x-BLOCK_HALF_SIZE,
                                                location.y-BLOCK_HALF_SIZE,
                                                location.z-BLOCK_HALF_SIZE),
                                                glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].bottomTextureBegin,0.0),
                                    glm::vec3(0.0,-1.0,0.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
                 vertices.push_back(basicVertex{glm::vec3(location.x+BLOCK_HALF_SIZE,
                                                location.y-BLOCK_HALF_SIZE,
                                                location.z-BLOCK_HALF_SIZE),
                                                glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].bottomTextureEnd,0.0),
                                    glm::vec3(0.0,-1.0,0.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
                 vertices.push_back(basicVertex{glm::vec3(location.x-BLOCK_HALF_SIZE,
                                                location.y-BLOCK_HALF_SIZE,
                                                location.z+BLOCK_HALF_SIZE),
                                                glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].bottomTextureBegin,1.0),
                                    glm::vec3(0.0,-1.0,0.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
                 vertices.push_back(basicVertex{glm::vec3(location.x+BLOCK_HALF_SIZE,
                                                location.y-BLOCK_HALF_SIZE,
                                                location.z-BLOCK_HALF_SIZE),
                                                glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].bottomTextureEnd,0.0),
                                    glm::vec3(0.0,-1.0,0.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
                 vertices.push_back(basicVertex{glm::vec3(location.x+BLOCK_HALF_SIZE,
                                                location.y-BLOCK_HALF_SIZE,
                                                location.z+BLOCK_HALF_SIZE),
                                                glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].bottomTextureEnd,1.0),
                                    glm::vec3(0.0,-1.0,0.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
                 *vertsCount +=6;
            }
        }
    }
    //positiveX
    tempBlock = getBlock(x+1, y, z);
    if(this->theWorld->bDatabase.blockTypes[tempBlock].opacity<1.0f)
    {
        if (tempBlock!= this->blocks[index])
        {
            vertices.push_back(basicVertex{glm::vec3(location.x+BLOCK_HALF_SIZE,
                                           location.y+BLOCK_HALF_SIZE,
                                           location.z+BLOCK_HALF_SIZE),
                                           glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].sideTextureBegin,1.0),
                               glm::vec3(1.0,0.0,0.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
            vertices.push_back(basicVertex{glm::vec3(location.x+BLOCK_HALF_SIZE,
                                           location.y-BLOCK_HALF_SIZE,
                                           location.z+BLOCK_HALF_SIZE),
                                           glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].sideTextureBegin,0.0),
                               glm::vec3(1.0,0.0,0.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
            vertices.push_back(basicVertex{glm::vec3(location.x+BLOCK_HALF_SIZE,
                                           location.y-BLOCK_HALF_SIZE,
                                           location.z-BLOCK_HALF_SIZE),
                                           glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].sideTextureEnd,0.0),
                               glm::vec3(1.0,0.0,0.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
            vertices.push_back(basicVertex{glm::vec3(location.x+BLOCK_HALF_SIZE,
                                           location.y+BLOCK_HALF_SIZE,
                                           location.z+BLOCK_HALF_SIZE),
                                           glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].sideTextureBegin,1.0),
                               glm::vec3(1.0,0.0,0.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
            vertices.push_back(basicVertex{glm::vec3(location.x+BLOCK_HALF_SIZE,
                                           location.y-BLOCK_HALF_SIZE,
                                           location.z-BLOCK_HALF_SIZE),
                                           glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].sideTextureEnd,0.0),
                               glm::vec3(1.0,0.0,0.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
            vertices.push_back(basicVertex{glm::vec3(location.x+BLOCK_HALF_SIZE,
                                           location.y+BLOCK_HALF_SIZE,
                                           location.z-BLOCK_HALF_SIZE),
                                           glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].sideTextureEnd,1.0),
                               glm::vec3(1.0,0.0,0.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
            *vertsCount +=6;
        }
    }
    //negativeX
    tempBlock = getBlock(x-1, y, z);
    if(this->theWorld->bDatabase.blockTypes[tempBlock].opacity<1.0f)
    {
        if (tempBlock!= this->blocks[index])
        {

             vertices.push_back(basicVertex{glm::vec3(location.x-BLOCK_HALF_SIZE,
                                            location.y+BLOCK_HALF_SIZE,
                                            location.z-BLOCK_HALF_SIZE),
                                            glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].sideTextureBegin,1.0),
                                glm::vec3(-1.0,0.0,0.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
             vertices.push_back(basicVertex{glm::vec3(location.x-BLOCK_HALF_SIZE,
                                            location.y-BLOCK_HALF_SIZE,
                                            location.z-BLOCK_HALF_SIZE),
                                            glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].sideTextureBegin,0.0),
                                glm::vec3(-1.0,0.0,0.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
             vertices.push_back(basicVertex{glm::vec3(location.x-BLOCK_HALF_SIZE,
                                            location.y-BLOCK_HALF_SIZE,
                                            location.z+BLOCK_HALF_SIZE),
                                            glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].sideTextureEnd,0.0),
                                glm::vec3(-1.0,0.0,0.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
             vertices.push_back(basicVertex{glm::vec3(location.x-BLOCK_HALF_SIZE,
                                            location.y+BLOCK_HALF_SIZE,
                                            location.z-BLOCK_HALF_SIZE),
                                            glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].sideTextureBegin,1.0),
                                glm::vec3(-1.0,0.0,0.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
             vertices.push_back(basicVertex{glm::vec3(location.x-BLOCK_HALF_SIZE,
                                            location.y-BLOCK_HALF_SIZE,
                                            location.z+BLOCK_HALF_SIZE),
                                            glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].sideTextureEnd,0.0),
                                glm::vec3(-1.0,0.0,0.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
             vertices.push_back(basicVertex{glm::vec3(location.x-BLOCK_HALF_SIZE,
                                            location.y+BLOCK_HALF_SIZE,
                                            location.z+BLOCK_HALF_SIZE),
                                            glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].sideTextureEnd,1.0),
                                glm::vec3(-1.0,0.0,0.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
             *vertsCount +=6;
        }
    }
    //positiveZ
    tempBlock = getBlock(x, y, z+1);
    if(this->theWorld->bDatabase.blockTypes[tempBlock].opacity<1.0f)
    {
        if (tempBlock!= this->blocks[index])
        {

            vertices.push_back(basicVertex{glm::vec3(location.x-BLOCK_HALF_SIZE,
                                           location.y+BLOCK_HALF_SIZE,
                                           location.z+BLOCK_HALF_SIZE),
                                           glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].sideTextureBegin,1.0),
                               glm::vec3(0.0,0.0,1.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
            vertices.push_back(basicVertex{glm::vec3(location.x-BLOCK_HALF_SIZE,
                                           location.y-BLOCK_HALF_SIZE,
                                           location.z+BLOCK_HALF_SIZE),
                                           glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].sideTextureBegin,0.0),
                               glm::vec3(0.0,0.0,1.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
            vertices.push_back(basicVertex{glm::vec3(location.x+BLOCK_HALF_SIZE,
                                           location.y-BLOCK_HALF_SIZE,
                                           location.z+BLOCK_HALF_SIZE),
                                           glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].sideTextureEnd,0.0),
                               glm::vec3(0.0,0.0,1.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
            vertices.push_back(basicVertex{glm::vec3(location.x-BLOCK_HALF_SIZE,
                                           location.y+BLOCK_HALF_SIZE,
                                           location.z+BLOCK_HALF_SIZE),
                                           glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].sideTextureBegin,1.0),
                               glm::vec3(0.0,0.0,1.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
            vertices.push_back(basicVertex{glm::vec3(location.x+BLOCK_HALF_SIZE,
                                           location.y-BLOCK_HALF_SIZE,
                                           location.z+BLOCK_HALF_SIZE),
                                           glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].sideTextureEnd,0.0),
                               glm::vec3(0.0,0.0,1.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
            vertices.push_back(basicVertex{glm::vec3(location.x+BLOCK_HALF_SIZE,
                                           location.y+BLOCK_HALF_SIZE,
                                           location.z+BLOCK_HALF_SIZE),
                                           glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].sideTextureEnd,1.0),
                               glm::vec3(0.0,0.0,1.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
            *vertsCount +=6;
        }
    }
    //negaticeZ
    tempBlock = getBlock(x, y, z-1);
    if(this->theWorld->bDatabase.blockTypes[tempBlock].opacity<1.0f)
    {
        if (tempBlock!= this->blocks[index])
        {

             vertices.push_back(basicVertex{glm::vec3(location.x+BLOCK_HALF_SIZE,
                                            location.y+BLOCK_HALF_SIZE,
                                            location.z-BLOCK_HALF_SIZE),
                                            glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].sideTextureBegin,1.0),
                                glm::vec3(0.0,0.0,-1.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
             vertices.push_back(basicVertex{glm::vec3(location.x+BLOCK_HALF_SIZE,
                                            location.y-BLOCK_HALF_SIZE,
                                            location.z-BLOCK_HALF_SIZE),
                                            glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].sideTextureBegin,0.0),
                                glm::vec3(0.0,0.0,-1.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
             vertices.push_back(basicVertex{glm::vec3(location.x-BLOCK_HALF_SIZE,
                                            location.y-BLOCK_HALF_SIZE,
                                            location.z-BLOCK_HALF_SIZE),
                                            glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].sideTextureEnd,0.0),
                                glm::vec3(0.0,0.0,-1.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
             vertices.push_back(basicVertex{glm::vec3(location.x+BLOCK_HALF_SIZE,
                                            location.y+BLOCK_HALF_SIZE,
                                            location.z-BLOCK_HALF_SIZE),
                                            glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].sideTextureBegin,1.0),
                                glm::vec3(0.0,0.0,-1.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
             vertices.push_back(basicVertex{glm::vec3(location.x-BLOCK_HALF_SIZE,
                                            location.y-BLOCK_HALF_SIZE,
                                            location.z-BLOCK_HALF_SIZE),
                                            glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].sideTextureEnd,0.0),
                                glm::vec3(0.0,0.0,-1.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
             vertices.push_back(basicVertex{glm::vec3(location.x-BLOCK_HALF_SIZE,
                                            location.y+BLOCK_HALF_SIZE,
                                            location.z-BLOCK_HALF_SIZE),
                                            glm::vec2(this->theWorld->bDatabase.blockTypes[this->blocks[index]].sideTextureEnd,1.0),
                                glm::vec3(0.0,0.0,-1.0),this->theWorld->bDatabase.blockTypes[this->blocks[index]].opacity});
             *vertsCount +=6;
        }
    }
}

void ChunkSection::makeMesh(ChunkMeshCollection* vertices, int *groundVerts, int* waterVerts)
{
    //std::cout<<"section"<<std::endl;
    for(int i = 0; i<CHUNK_VOLUME; i++)
    {
        //if(this->shouldMakeLayer((i / (CHUNK_AREA))))
        //{
        if(this->blocks[i]!=0)
        {
            if(this->blocks[i]==8)
            {
                addBlockMesh(vertices->waterMesh, i, waterVerts);
            }
            else
            {
                addBlockMesh(vertices->solidMesh, i, groundVerts);
            }
        }
        //}
    }
}

Layer &ChunkSection::getLayer(int y)
{
    if (y == -1)
    {
        if(location.y<=0)
        {
            return this->theWorld->getChunk(location.x, location.z)
                   .getSection(0)
                   .getLayer(0);
        }
        else
        {
            return this->theWorld->getChunk(location.x, location.z)
                   .getSection(location.y - 1)
                   .getLayer(CHUNK_SIZE - 1);
        }
    }
    else if (y == CHUNK_SIZE)
    {
        return this->theWorld->getChunk(location.x, location.z)
               .getSection(location.y + 1)
               .getLayer(0);
    }
    else
    {
        return layers[y];
    }
}

void ChunkSection::setBlock(int x, int y, int z, int blockId)
{
    if (outOfBounds(x) || outOfBounds(y) || outOfBounds(z))
    {
        auto location = toWorldPosition(x, y, z);
        theWorld->setBlock(location.x, location.y, location.z, blockId);
        return;
    }

    layers[y].update(blockId);

    blocks[getIndex(x, y, z)] = blockId;
}

int ChunkSection::getBlock(int x, int y, int z)
{
    if (outOfBounds(x) || outOfBounds(y) || outOfBounds(z))
    {
        auto location = toWorldPosition(x, y, z);
        return theWorld->getBlock(location.x, location.y, location.z);
    }
    return blocks[getIndex(x, y, z)];
}

bool ChunkSection::shouldMakeLayer(int y)
{
    auto adjIsSolid = [&](int dx, int dz)
    {
        //std::cout<<"adjlayer"<<std::endl;
        ChunkSection &sect = this->getAdjacent(dx, dz);
        return sect.getLayer(y).isAllSolid();
    };
    //std::cout<<"should layer: "<<y<<std::endl;
    return (!this->getLayer(y).isAllSolid()) ||
           (!this->getLayer(y + 1).isAllSolid()) ||
           (!this->getLayer(y - 1).isAllSolid()) ||

           (!adjIsSolid(1, 0)) || (!adjIsSolid(0, 1)) || (!adjIsSolid(-1, 0)) ||
           (!adjIsSolid(0, -1));
}
