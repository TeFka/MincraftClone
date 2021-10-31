
#include "../Inc/World.h"

void World::updateVAO()
{
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(basicVertex)*this->vertices.solidMesh.size(), this->vertices.solidMesh.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(basicVertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE, sizeof(basicVertex), (void*)offsetof(basicVertex, textr));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,3, GL_FLOAT, GL_FALSE, sizeof(basicVertex), (void*)offsetof(basicVertex, norm));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3,1, GL_FLOAT, GL_FALSE, sizeof(basicVertex), (void*)offsetof(basicVertex, opacity));
    glEnableVertexAttribArray(3);

    glBindVertexArray(this->trnVAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->trnVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(basicVertex)*this->vertices.waterMesh.size(), this->vertices.waterMesh.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(basicVertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE, sizeof(basicVertex), (void*)offsetof(basicVertex, textr));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,3, GL_FLOAT, GL_FALSE, sizeof(basicVertex), (void*)offsetof(basicVertex, norm));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3,1, GL_FLOAT, GL_FALSE, sizeof(basicVertex), (void*)offsetof(basicVertex, opacity));
    glEnableVertexAttribArray(3);
    glBindVertexArray(0);
}

void World::deleteChunkMesh(int x, int z)
{
    if(this->getChunk(x,z).deleteMeshes())
    {
        for (auto &chunk : this->activeChunks)
        {
            if(chunk.second.getGroundVertNr()>0)
            {
                if(this->getChunk(x,z).getGroundVertStart()<chunk.second.getGroundVertStart())
                {
                    chunk.second.setGroundVertStart(chunk.second.getGroundVertStart()-this->getChunk(x,z).getGroundVertNr());
                }
            }
            if(chunk.second.getWaterVertNr()>0)
            {
                if(this->getChunk(x,z).getWaterVertStart()<chunk.second.getWaterVertStart())
                {
                    chunk.second.setWaterVertStart(chunk.second.getWaterVertStart()-this->getChunk(x,z).getWaterVertNr());
                }
            }
        }
        this->getChunk(x,z).refreshMeshValues();
    }

}

void World::deleteChunk(int x, int z)
{
     //std::cout<<"deleting chunk"<<std::endl;
    if (activeChunks.find({x, z}) != activeChunks.end())
    {
        this->deleteChunkMesh(x, z);
        this->activeChunks.erase({x, z});
    }
    //std::cout<<"deleted"<<std::endl;
}

void World::initChunk(int x, int z)
{
    for (int nx = -1; nx <= 1; nx++)
    {
        for (int nz = -1; nz <= 1; nz++)
        {
            getChunk(x + nx,z + nz).load(this->worldGenerator);
        }
    }
    getChunk(x, z).makeMesh();
}

void World::loadChunks(glm::vec3 playerPos)
{
    int playerX = playerPos.x / CHUNK_SIZE;
    int playerZ = playerPos.z / CHUNK_SIZE;
    for (int i = 0; i < loadDistance; i++)
    {
        //std::this_thread::sleep_for(std::chrono::milliseconds(1));
        //int minX = std::max(playerX - i, 0);
        //int minZ = std::max(playerZ - i, 0);
        int minX = playerX - i;
        int minZ = playerZ - i;
        int maxX = playerX + i;
        int maxZ = playerZ + i;

        for (int x = minX; x <= maxX; ++x)
        {
            for (int z = minZ; z <= maxZ; ++z)
            {
                this->chunksToGenerate.push_back({x,z});
            }
        }
    }
}

World::World(Texture* mainTextr, glm::vec3 &playerPos)
{
    this->texture = mainTextr;

    glGenVertexArrays(1,&this->VAO);
    glGenVertexArrays(1,&this->trnVAO);
    glGenBuffers(1,&this->VBO);
    glGenBuffers(1,&this->trnVBO);
    /*for (int i = 0; i < 1; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        updateThreads.emplace_back([&]() { update(playerPos); });
    }*/
}

World::~World(){
    this->updating = 0;
    /*for (auto &thread : updateThreads) {
        thread.join();
    }*/
}

glm::vec3 World::setSpawn()
{
    //int attempts = 0;
    int chunkX = -1;
    int chunkZ = -1;
    int blockX = 0;
    int blockZ = 0;
    int blockY = 180;

    auto h = worldGenerator.getMinimumSpawnHeight();

    /*while (blockY <= h)
    {
        m_chunkManager.unloadChunk(chunkX, chunkZ);

        chunkX = RandomSingleton::get().intInRange(100, 200);
        chunkZ = RandomSingleton::get().intInRange(100, 200);
        blockX = RandomSingleton::get().intInRange(0, 15);
        blockZ = RandomSingleton::get().intInRange(0, 15);

        m_chunkManager.loadChunk(chunkX, chunkZ);
        blockY =
            m_chunkManager.getChunk(chunkX, chunkZ).getHeightAt(blockX, blockZ);
        attempts++;
    }*/

    int worldX = chunkX * CHUNK_SIZE + blockX;
    int worldZ = chunkZ * CHUNK_SIZE + blockZ;

    for (int x = chunkX - 1; x <= chunkX + 1; ++x)
    {
        for (int z = chunkZ - 1; z <= chunkZ + 1; ++z)
        {
            //std::unique_lock<std::mutex> lock(m_mainMutex);
            this->initChunk(x, z);
        }
    }
    return glm::vec3(worldX, blockY, worldZ);
}

int World::getBlockCount()
{
    return this->activeBlocks.size();
}

std::vector<levelObject*> World::getBlocks()
{
    return this->activeBlocks;
}

float World::getBlockSize()
{
    return this->blockSize;
}

VectorXZ World::getBlockXZ(int x, int z)
{
    return {((x % CHUNK_SIZE)*(x%CHUNK_SIZE>=0)*(x>=0))+((((CHUNK_SIZE)*(x<(-CHUNK_SIZE)))+
                                                          ((x % CHUNK_SIZE)+(CHUNK_SIZE*(x>(-CHUNK_SIZE)))))*(x%CHUNK_SIZE<0)*(x<0)),
            ((z % CHUNK_SIZE)*(z%CHUNK_SIZE>=0)*(z>=0))+((((CHUNK_SIZE)*(z<(-CHUNK_SIZE)))+
                                                          ((z % CHUNK_SIZE)+(CHUNK_SIZE*(z>(-CHUNK_SIZE)))))*(z%CHUNK_SIZE<0)*(z<0))};
}

VectorXZ World::getChunkXZ(int x, int z)
{
    return {(x / CHUNK_SIZE)-((x % CHUNK_SIZE!=0)*(x<0)), (z / CHUNK_SIZE)-((z % CHUNK_SIZE!=0)*(z<0))};
}

Chunk& World::getChunk(int x, int z)
{
    VectorXZ key{x, z};
    if (!(activeChunks.find({x, z}) != activeChunks.end())){
        Chunk chunk(this, &this->vertices,x, z);
        activeChunks.emplace(key, std::move(chunk));
    }
    return activeChunks[key];
}

int World::getBlock(int x, int y, int z)
{
    //std::cout<<"pos: "<<x<<"  "<<z<<std::endl;
    auto bp = getBlockXZ(x, z);
    auto chunkPosition = getChunkXZ(x, z);
     //std::cout<<"blockPos: "<<bp.x<<"  "<<bp.z<<std::endl;
      //std::cout<<"ChunkPos: "<<chunkPosition.x<<"  "<<chunkPosition.z<<std::endl;
    return getChunk(chunkPosition.x, chunkPosition.z).getBlock(bp.x, y, bp.z);
}

void  World::setBlock(int x, int y, int z, int blockId)
{
    if (y <= 0)
    {
        return;
    }

    auto bp = getBlockXZ(x, z);
    auto chunkPosition = getChunkXZ(x, z);

    getChunk(chunkPosition.x, chunkPosition.z)
    .setBlock(bp.x, y, bp.z, blockId);
}

void World::update(glm::vec3 &playerPos, float deltaTime)
{
    //std::cout<<"updating"<<std::endl;
    //while(this->updating){
    if(this->chunkUpdate<this->chunksToGenerate.size())
    {
        //std::cout<<"create chunk"<<std::endl;
        this->initChunk(this->chunksToGenerate[this->chunkUpdate].x, this->chunksToGenerate[this->chunkUpdate].z);
        this->chunkUpdate++;
        //std::cout<<"created"<<std::endl;
    }
    else
    {
        //std::cout<<"load chunks"<<std::endl;
        this->chunksToGenerate.clear();
        this->chunkUpdate = 0;
        this->loadChunks(playerPos);
        //std::cout<<"loaded"<<std::endl;
    }
    //std::cout<<"check to delete"<<std::endl;
    for (auto &daChunk : this->activeChunks)
    {
        glm::ivec2 chunkPos = daChunk.second.getLocation();
        if((((((int)playerPos.x/CHUNK_SIZE)-chunkPos.x)*(1-(2*(((int)playerPos.x/CHUNK_SIZE)<chunkPos.x))))>(loadDistance+1))||
                (((((int)playerPos.z/CHUNK_SIZE)-chunkPos.y)*(1-(2*(((int)playerPos.z/CHUNK_SIZE)<chunkPos.y))))>(loadDistance+1)))
        {
            this->deleteChunk(chunkPos.x,chunkPos.y);
            break;
        }
    }
    this->movementCounter-=deltaTime;
        if(this->movementCounter<=0){
            for(int i = 0;i<this->vertices.waterMesh.size();i++){
                this->vertices.waterMesh[i].pos.y+=(0.1*(sin(glfwGetTime())));
                if(this->vertices.waterMesh[i].pos.y>WATER_LEVEL){
                    this->vertices.waterMesh[i].pos.y=WATER_LEVEL;
                }
            }
            this->movementCounter=0.2;
        }
    //}
    //std::cout<<"updated"<<std::endl;
}

void World::drawMesh(Shader* shad)
{
    //std::cout<<"solid mesh: "<<this->vertices.solidMesh.size()<<std::endl;
    //std::cout<<this->activeChunks.size()<<std::endl;
    this->updateVAO();
    glBindVertexArray(this->VAO);
    shad->setVec4f(glm::vec4(0.0,1.0,0.0,1.0),"lCol");
    shad->set1i(this->texture->getUnit(),"textare");
    shad->set1i(1,"useText");
    this->texture->bindT();
    shad->use();
    glDrawArrays(GL_TRIANGLES,0,this->vertices.solidMesh.size());
    glDepthMask(GL_FALSE);

    //trasparent part
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBindVertexArray(this->trnVAO);
    shad->use();
    glDrawArrays(GL_TRIANGLES,0,this->vertices.waterMesh.size());
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    //std::cout<<"drawn"<<std::endl;
}

/* void World::setDestroyedBlock(int type,int biomeNum,int chunkNum,int blockColumnNum,int blockNum)
 {
     //std::cout<<this->destroyedBlocks[b]->biomeNum<<"  "<<this->destroyedBlocks[b]->chunkNum<<"  "<<this->destroyedBlocks[b]->blockColumnNum<<"  "<<this->destroyedBlocks[b]->blockNum<<std::endl;
     //this->destroyedBlocks.push_back(new destroyedBlock{type,biomeNum,chunkNum,blockColumnNum,blockNum});
     for(int i = 0;i<this->activeChunks.size();i++){
         if(chunkNum == this->activeChunks[i]->num){
             this->chunksToUpdate.push_back(i);
             break;
         }
     }
 }*/
