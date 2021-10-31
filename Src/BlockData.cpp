#include "../Inc/BlockData.h"

BlockDatabase::BlockDatabase(){

    //air fill
    this->blockTypes[0]= blockData{0,0,0,0,0,0,0.0,0};
    //grass block
    this->blockTypes[1]= blockData{0,1.0f/this->atlasSize,2.0f/this->atlasSize,3.0f/this->atlasSize,1.0f/this->atlasSize,2.0f/this->atlasSize,1.0f,1};
    //dirt block
    this->blockTypes[2]= blockData{1.0f/this->atlasSize,2.0f/this->atlasSize,1.0f/this->atlasSize,2.0f/this->atlasSize,1.0f/this->atlasSize,2.0f/this->atlasSize,1.0f,1};
    //stone block
    this->blockTypes[3]= blockData{3.0f/this->atlasSize,4.0f/this->atlasSize,3.0f/this->atlasSize,4.0f/this->atlasSize,3.0f/this->atlasSize,4.0f/this->atlasSize,1.0f,};
    //sand block
    this->blockTypes[4]= blockData{7.0f/this->atlasSize,8.0f/this->atlasSize,7.0f/this->atlasSize,8.0f/this->atlasSize,7.0f/this->atlasSize,8.0f/this->atlasSize,1.0f,1};
    //wood block
    this->blockTypes[5]= blockData{8.0f/this->atlasSize,9.0f/this->atlasSize,5.0f/this->atlasSize,6.0f/this->atlasSize,8.0f/this->atlasSize,9.0f/this->atlasSize,1.0f,1};
    //leaf block
    this->blockTypes[6]= blockData{6.0f/this->atlasSize,7.0f/this->atlasSize,6.0f/this->atlasSize,7.0f/this->atlasSize,6.0f/this->atlasSize,7.0f/this->atlasSize,1.0f,1};
    //cactus block
    this->blockTypes[7]= blockData{9.0f/this->atlasSize,10.0f/this->atlasSize,9.0f/this->atlasSize,10.0f/this->atlasSize,9.0f/this->atlasSize,10.0f/this->atlasSize,1.0f,1};
    //water block
    this->blockTypes[8]= blockData{4.0f/this->atlasSize,5.0f/this->atlasSize,4.0f/this->atlasSize,5.0f/this->atlasSize,4.0f/this->atlasSize,5.0f/this->atlasSize,0.5f,0};
    //???? block
    //this->blockTypes[8]= blockData{0,1.0f/this->atlasSize,2.0f/this->atlasSize,3.0f/this->atlasSize,1.0f/this->atlasSize,2.0f/this->atlasSize,1.0};
    //???? block
    //this->blockTypes[9]= blockData{0,1.0f/this->atlasSize,2.0f/this->atlasSize,3.0f/this->atlasSize,1.0f/this->atlasSize,2.0f/this->atlasSize,1.0};
}
