#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

#define _USE_MATH_DEFINES

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>
#include<sstream>
#include<fstream>
#include<thread>
#include<map>
#include<math.h>
#include<vector>
#include<array>

#include <sys/time.h>

#include<SOIL2/SOIL2.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

//CONSTANTS
const int CHUNK_SIZE = 16;
const int CHUNK_AREA = 256;
const int CHUNK_VOLUME = 4096;
const float BLOCK_HALF_SIZE = 0.5;
const int WATER_LEVEL = 64;

//blocks
const int GRASS_B = 1;
const int DIRT_B = 2;
const int STONE_B = 3;
const int SAND_B = 4;
const int WOOD_B = 5;
const int LEAF_B = 6;
const int CACTUS_B = 7;
const int WATER_B = 8;


//STRUCTURES

struct basicVertex
{
    glm::vec3 pos;
    glm::vec2 textr;
    glm::vec3 norm;
    float opacity;
};

struct screenVertex
{
    glm::vec3 pos;
    glm::vec2 textr;
};

struct Character
{
    GLuint text;
    glm::ivec2 siz;
    glm::ivec2 bear;
    GLuint advance;
};

struct levelObject
{
    int x;
    int y;
    int z;
    glm::vec3 pos;
};

struct Bullet
{
    glm::vec3 pos;
    glm::vec3 siz;
    glm::vec3 direction;
    glm::mat4 rotation;
    float speed;
    glm::vec4 col;
    GLuint textrUn;
    GLuint textrId;
};

struct NoiseParameters {
    int octaves;
    int amplitude;
    int smoothness;
    int heightOffset;
    double roughness;
};

struct ChunkMeshCollection
{
    std::vector<basicVertex> solidMesh;
    std::vector<basicVertex> waterMesh;
};

#endif
