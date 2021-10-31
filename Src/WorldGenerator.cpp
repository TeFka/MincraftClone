#include "../Inc/WorldGenerator.h"

#include <functional>
#include <iostream>

#include"Random.h"
#include"Chunk.h"

namespace
{
    Random<> rand;
const int seed = rand.intInRange(424, 325322);
}

//NoiseGenerator WorldGenerator::biomeNoiseGen(seed * 2);

WorldGenerator::WorldGenerator()
    : activeBiome(seed)
{
    biomeNoiseGen.setSeed(seed*2);
    NoiseParameters biomeParams;
    biomeParams.octaves = 8;
    biomeParams.amplitude = 80;
    biomeParams.smoothness = 900;
    biomeParams.heightOffset = -5;
    biomeParams.roughness = 0.5;
    biomeNoiseGen.setParameters(biomeParams);
}

float WorldGenerator::smoothstep(float edge0, float edge1, float x)
{
    // Scale, bias and saturate x to 0..1 rangedgfsfdf
    x = x * x * (3 - 2 * x);
    // Evaluate polynomial
    return (edge0 * x) + (edge1 * (1 - x));
}

float WorldGenerator::smoothInterpolation(float bottomLeft, float topLeft, float bottomRight,
        float topRight, float xMin, float xMax, float zMin,
        float zMax, float x, float z)
{
    float width = xMax - xMin, height = zMax - zMin;
    float xValue = 1 - (x - xMin) / width;
    float zValue = 1 - (z - zMin) / height;

    // std::cout << xValue << std::endl;

    float a = smoothstep(bottomLeft, bottomRight, xValue);
    float b = smoothstep(topLeft, topRight, xValue);
    return smoothstep(a, b, zValue);
}


void WorldGenerator::generateTerrainFor(Chunk &chunk)
{
    this->activeChunk = &chunk;

    auto location = chunk.getLocation();
    random.setSeed((location.x ^ location.y) << 2);
    getBiomeMap();
    getHeightMap();
    auto maxHeight = *std::max_element(heightMap.begin(), heightMap.end());
    maxHeight = std::max(maxHeight, WATER_LEVEL);
    setBlocks(maxHeight);
}

int WorldGenerator::getMinimumSpawnHeight()
{
    return WATER_LEVEL;
}

void WorldGenerator::getHeightIn(int xMin, int zMin, int xMax,
                                 int zMax)
{

    auto getHeightAt = [&](int x, int z)
    {
        this->setBiome(x, z);

        return this->activeBiome.getHeight(x, z, activeChunk->getLocation().x,
                               activeChunk->getLocation().y);
    };

    float bottomLeft = static_cast<float>(getHeightAt(xMin, zMin));
    float bottomRight = static_cast<float>(getHeightAt(xMax, zMin));
    float topLeft = static_cast<float>(getHeightAt(xMin, zMax));
    float topRight = static_cast<float>(getHeightAt(xMax, zMax));

    for (int x = xMin; x < xMax; ++x)
    {
        for (int z = zMin; z < zMax; ++z)
        {
            if (x == CHUNK_SIZE)
                continue;
            if (z == CHUNK_SIZE)
                continue;

            float h = smoothInterpolation(
                          bottomLeft, topLeft, bottomRight, topRight,
                          static_cast<float>(xMin), static_cast<float>(xMax),
                          static_cast<float>(zMin), static_cast<float>(zMax),
                          static_cast<float>(x), static_cast<float>(z));

            heightMap[x*CHUNK_SIZE+z] = static_cast<int>(h);
        }
    }
}

void WorldGenerator::getHeightMap()
{
    constexpr static auto HALF_CHUNK = CHUNK_SIZE / 2;
    constexpr static auto CHUNK = CHUNK_SIZE;

    getHeightIn(0, 0, HALF_CHUNK, HALF_CHUNK);
    getHeightIn(HALF_CHUNK, 0, CHUNK, HALF_CHUNK);
    getHeightIn(0, HALF_CHUNK, HALF_CHUNK, CHUNK);
    getHeightIn(HALF_CHUNK, HALF_CHUNK, CHUNK, CHUNK);
}

void WorldGenerator::getBiomeMap()
{
    auto location = activeChunk->getLocation();

    for (int x = 0; x < CHUNK_SIZE + 1; x++)
    {
        for (int z = 0; z < CHUNK_SIZE + 1; z++)
        {
            double h = biomeNoiseGen.getHeight(x, z, location.x + 10,
                                               location.y + 10);
            biomeMap[x*CHUNK_SIZE+z] = static_cast<int>(h);
        }
    }
}

void WorldGenerator::setBlocks(int maxHeight)
{
    std::vector<glm::ivec3> trees;
    //std::vector<glm::ivec3> plants;

    for (int y = 0; y < maxHeight + 1; y++)
    {
        for (int x = 0; x < CHUNK_SIZE; x++){
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                int height = heightMap[x*CHUNK_SIZE+z];
                this->setBiome(x, z);

                if (y > height)
                {
                    if (y <= WATER_LEVEL)
                    {
                        this->activeChunk->setBlock(x, y, z, WATER_B);
                    }
                    continue;
                }
                else if (y == height)
                {
                    if (y >= WATER_LEVEL)
                    {
                        if (y < WATER_LEVEL + 4)
                        {
                            this->activeChunk->setBlock(x, y, z,
                                                        activeBiome.getBeachBlock(random));
                            continue;
                        }

                        if (random.intInRange(0, activeBiome.getTreeFrequency()) ==
                                5)
                        {
                            activeBiome.makeTree(random, *this->activeChunk, x, y+1, z);
                        }
                        /*if (random.intInRange(0, activeBiome.getPlantFrequency()) ==
                                5)
                        {
                            //plants.emplace_back(x, y + 1, z);
                        }*/
                        this->activeChunk->setBlock(
                            x, y, z, activeBiome.getTopBlock(random));
                    }
                    else
                    {
                        this->activeChunk->setBlock(x, y, z,
                                                    activeBiome.getUnderWaterBlock(random));
                    }
                }
                else if (y > height - 3)
                {
                    this->activeChunk->setBlock(x, y, z, DIRT_B);
                }
                else
                {
                    this->activeChunk->setBlock(x, y, z, STONE_B);
                }
            }
        }
    }
    /*for (auto &plant : plants) {
        int x = plant.x;
        int z = plant.z;

        auto block = getBiome(x, z).getPlant(m_random);
        m_pChunk->setBlock(x, plant.y, z, block);
    }*/
}

void WorldGenerator::setBiome(int x, int z)
{
    int biomeValue = biomeMap[x*CHUNK_SIZE+z];

    if (biomeValue > 160||biomeValue < 100)
    {
        this->activeBiome.setType(FOREST_BIOME);
    }
    else if (biomeValue > 140)
    {
        this->activeBiome.setType(OCEAN_BIOME);
    }
    else
    {
        this->activeBiome.setType(DESERT_BIOME);
    }
}
