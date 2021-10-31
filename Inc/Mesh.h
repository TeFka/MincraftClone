
#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include"struct.h"
#include"Shader.h"
#include"Texture.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
//#include <assimp/assimp_utilities.hpp>

const int NUM_BONES_PER_VERTEX = 5;

struct boneInfo
{
    glm::mat4 BoneOffset;
    glm::mat4 FinalTransformation;
};

struct boneData
{
    int IDs[NUM_BONES_PER_VERTEX];
    float weights[NUM_BONES_PER_VERTEX];

    boneData()
    {
        reset();
    }
    void reset()
    {
        for(int i = 0; i<NUM_BONES_PER_VERTEX; i++)
        {

            IDs[i] = 0;
            weights[i] = 0;
        }
    }

    void addBoneData(int BoneID, float Weight)
    {
        for (int i = 0 ; i < sizeof(weights)/sizeof(weights[0]); i++)
        {
            if (weights[i] == 0.0)
            {
                IDs[i] = BoneID;
                weights[i] = Weight;
                return;
            }
            else if(i>=4){
                IDs[i] = 0.0;
                weights[i] = 0.0;
                return;
            }
        }
        // should never get here - more bones than we have space for
        assert(0);
    }
};

class AssimpMesh
{
public:
    // constructor
    AssimpMesh(std::vector<basicVertex>, std::vector<unsigned int>, std::vector<Texture*>, std::vector<boneData>);

    std::vector<basicVertex> getVert();

    // render the mesh
    void Draw(Shader *);

private:

    std::vector<basicVertex>  vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture*>      textures;
    std::vector<boneData>     bones;
    unsigned int VAO;

    // render data
    unsigned int VBO, boneVBO;

    // initializes all the buffer objects/arrays
    void setupMesh();
};
#endif
