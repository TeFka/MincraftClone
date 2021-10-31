#ifndef BIOME_H_INCLUDED
#define BIOME_H_INCLUDED

#include"struct.h"
#include"Random.h"
#include"NoiseGenerator.h"

using Rand = Random<std::minstd_rand>;

class Chunk;

enum biomeType{
    FOREST_BIOME = 0,
    DESERT_BIOME = 1,
    OCEAN_BIOME = 2
};

class Biome {
  public:
    Biome(int);
    ~Biome() = default;

    //ChunkBlock getPlant(Rand &rand);
    int getTopBlock(Rand&);
    int getUnderWaterBlock(Rand&);
    int getBeachBlock(Rand&);
    void makeTree(Rand&, Chunk&, int, int,int);

    int getHeight(int, int, int, int);
    int getTreeFrequency();
    int getPlantFrequency();
    void setType(biomeType);

  protected:
    NoiseParameters noiseParams;

  private:
    NoiseGenerator heightGenerator[3];
    int treeFrequency[3];
    int plantFrequency[3];
    biomeType type;
};

#endif // BIOME_H_INCLUDED
