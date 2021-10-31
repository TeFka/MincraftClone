

#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include"Mesh.h"

class AssimpModel
{
public:

    Assimp::Importer importer;

    const aiScene* scene;

    // model data
    std::vector<Texture*> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<AssimpMesh*>  meshes;
    std::string directory;
    glm::vec3 pos = glm::vec3(1.0);
    glm::vec3 faceDirection;
    float edges[6] = {0,0,0,0,0,0};
    glm::vec3 dimensions;
    glm::vec3 sizeIncrease;
    glm::mat4 modelMat = glm::mat4(1.0);
    bool gammaCorrection;

    int verticesNr = 0;

    std::vector<glm::mat4> Transforms;

    std::vector<boneData> bones;
    std::vector<glm::mat4> boneOffset;

    glm::mat4 globalInverseTransform;

    std::map<std::string,int> m_BoneMapping; // maps a bone name to its index
    int m_NumBones = 0;
    std::string index, onePart, secondPart;

    float startTime;
    float passedTime;

    // constructor, expects a filepath to a 3D model.
    AssimpModel(std::string, glm::vec3 = glm::vec3(0.0),bool = false);

    //AssimModel(const AssimpModel &modX, glm::vec3 = glm::vec3(0.0));

    void setPos(glm::vec3);

    void setFaceDir(glm::vec3);

    glm::vec3 getBaseSize();
    void setSizeIncrease(float);
    // draws the model, and thus all its meshes
    void Draw(Shader *);

private:

    void getPlayerRotation(glm::vec3, glm::vec3);

    int FindPosition(float, const aiNodeAnim*);

    int FindRotation(float, const aiNodeAnim*);

    int FindScaling(float, const aiNodeAnim*);

    const aiNodeAnim* FindNodeAnim(const aiAnimation*, aiNode*);

    void CalcInterpolatedPosition(aiVector3D&, float, const aiNodeAnim*);

    void CalcInterpolatedRotation(aiQuaternion&, float, const aiNodeAnim*);

    void CalcInterpolatedScaling(aiVector3D&, float, const aiNodeAnim*);
    void ReadNodeHeirarchy(float, aiNode*, glm::mat4);

    void BoneTransform(float);

    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes std::vector.
    void loadModel(std::string &);

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode *);

    void loadBones(const aiMesh* );

    AssimpMesh* processMesh(aiMesh *);

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    std::vector<Texture*> loadMaterialTextures(aiMaterial *, aiTextureType, std::string);
};
#endif
