#include "../Inc/Biome.h"
#include "../Inc/Chunk.h"

Biome::Biome(int seed)
{
    heightGenerator[0].setSeed(seed);
    heightGenerator[1].setSeed(seed);
    heightGenerator[2].setSeed(seed);
    this->type = FOREST_BIOME;
    NoiseParameters heightParams;
    //forest
    this->treeFrequency[FOREST_BIOME] = 55;
    this->plantFrequency[FOREST_BIOME] = 75;

    heightParams.octaves = 5;
        heightParams.amplitude = 100;
        heightParams.smoothness = 195;
        heightParams.heightOffset = -30;
        heightParams.roughness = 0.52;
    this->heightGenerator[FOREST_BIOME].setParameters(heightParams);
    //desert
        this->treeFrequency[DESERT_BIOME] = 1350;
        this->plantFrequency[DESERT_BIOME] = 500;

        heightParams.octaves = 9;
        heightParams.amplitude = 80;
        heightParams.smoothness = 335;
        heightParams.heightOffset = -7;
        heightParams.roughness = 0.56;
        this->heightGenerator[DESERT_BIOME].setParameters(heightParams);
    //ocean
    this->treeFrequency[OCEAN_BIOME] = 50;
        this->plantFrequency[OCEAN_BIOME] = 100;

        heightParams.octaves = 7;
        heightParams.amplitude = 43;
        heightParams.smoothness = 55;
        heightParams.heightOffset = 0;
        heightParams.roughness = 0.50;
        this->heightGenerator[OCEAN_BIOME].setParameters(heightParams);
}

void Biome::setType(biomeType bType)
{
    this->type = bType;
}

int Biome::getTopBlock(Rand &rand)
{
    switch(this->type)
    {
    case FOREST_BIOME:
        return rand.intInRange(0, 10) < 8 ? GRASS_B : DIRT_B;
        break;
    case DESERT_BIOME:
        return SAND_B;
        break;
    case OCEAN_BIOME:
        return rand.intInRange(0, 10) < 8 ? GRASS_B : DIRT_B;
        break;
    }
}

int Biome::getUnderWaterBlock(Rand &rand)
{
    switch(this->type)
    {
    case FOREST_BIOME:
        return DIRT_B;
        break;
    case DESERT_BIOME:
        return SAND_B;
        break;
    case OCEAN_BIOME:
        return rand.intInRange(0, 10) < 8 ? DIRT_B : SAND_B;
        break;
    }
}

int Biome::getBeachBlock(Rand &rand)
{
    return SAND_B;
}

int Biome::getHeight(int x, int z, int chunkX, int chunkZ)
{
    return heightGenerator[this->type].getHeight(x, z, chunkX, chunkZ);
}

int Biome::getTreeFrequency()
{
    return treeFrequency[this->type];
}

int Biome::getPlantFrequency()
{
    return plantFrequency[this->type];
}

void Biome::makeTree(Random<std::minstd_rand> &rand, Chunk &chunk, int x, int y,
                     int z)
{
    switch(this->type)
    {
    case FOREST_BIOME:
    {
        int h = rand.intInRange(4, 7);
        int leafSize = rand.intInRange(2, 3);
        int newY = h + y;

        for(int i = y; i<newY; i++)
        {
            chunk.setBlock(x, i, z, WOOD_B);
        }

        for(int ty =newY-leafSize; ty<newY+leafSize; ty++)
        {
            for(int tx =x-leafSize; tx<x+leafSize; tx++)
            {
                for(int tz =z-leafSize; tz<z+leafSize; tz++)
                {
                    if(tx!=x||tz!=z||ty>newY)
                    {
                        if(rand.intInRange(0,1))
                        {
                        chunk.setBlock(tx, ty, tz, LEAF_B);
                        }
                    }
                }
            }
        }
        break;
    }
    case DESERT_BIOME:
    {
        int h = rand.intInRange(4, 7);
        int newY = h + y;

        for(int i = y; i<newY; i++)
        {
            chunk.setBlock(x, i, z, CACTUS_B);
        }
        break;
    }
    case OCEAN_BIOME:
    {

        break;
    }
    }
}
