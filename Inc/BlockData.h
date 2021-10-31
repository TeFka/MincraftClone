#ifndef BLOCKDATA_H_INCLUDED
#define BLOCKDATA_H_INCLUDED

#include <iostream>
#include<array>

struct blockData{
    float topTextureBegin;
    float topTextureEnd;
    float sideTextureBegin;
    float sideTextureEnd;
    float bottomTextureBegin;
    float bottomTextureEnd;
    float opacity;
    int canColide;
};

class BlockDatabase{
  public:

    BlockDatabase();

    int atlasSize = 10;
    const int blockTypeNum = 8;
    std::array<blockData, 9> blockTypes;
};

#endif // BLOCKDATA_H_INCLUDED
