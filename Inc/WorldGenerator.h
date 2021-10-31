#ifndef WORLDGENERATOR_H_INCLUDED
#define WORLDGENERATOR_H_INCLUDED

#include<algorithm>

#include"struct.h"
#include "Random.h"
#include"NoiseGenerator.h"
#include"ChunkSection.h"
#include"Biome.h"

class Chunk;

class WorldGenerator{
  public:
    WorldGenerator();

    void generateTerrainFor(Chunk &chunk);
    int getMinimumSpawnHeight();

  private:
    float smoothstep(float, float, float);
    float smoothInterpolation(float, float, float,float, float, float, float,float, float, float);
    static void setUpNoise();

    void setBiome(int, int);
    void setBlocks(int maxHeight);

    void getHeightIn(int, int, int, int);
    void getHeightMap();
    void getBiomeMap();

    Biome &getBiome(int, int);

    std::array<int, CHUNK_AREA> heightMap;
    std::array<int, ((CHUNK_SIZE + 1)*(CHUNK_SIZE + 1))> biomeMap;

    Random<std::minstd_rand> random;

    NoiseGenerator biomeNoiseGen;

    Biome activeBiome;

    Chunk *activeChunk = nullptr;
};

#endif // WORLDGENERATOR_H_INCLUDED
