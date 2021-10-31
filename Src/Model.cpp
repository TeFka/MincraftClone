#include "../Inc/model.h"
#include "../Inc/individualFunctions.h"

AssimpModel::AssimpModel(std::string path, glm::vec3 pos,bool gamma) : gammaCorrection(gamma)
{
    loadModel(path);
    this->pos = pos;
    this->dimensions.x = this->edges[0]-this->edges[1];
    this->dimensions.y = this->edges[2]-this->edges[3];
    this->dimensions.z = this->edges[4]-this->edges[5];
    this->startTime = GetCurrentTimeMillis();
}
/*
AssimpModel::AssimModel(const AssimpModel &modX, glm::vec3 pos)
{
    this->textures_loaded=modX.textures_loaded;
    this->meshes = modX.meshes;
    this->directory = modX.directory;
    this->verticesNr = modX.verticesNr;
    this->bones = modX.bones;
    this->boneOffset = modX.boneOffset;
    this->globalInverseTransform = modX.globalInverseTransform;
    this->m_BoneMapping = modX.m_BoneMapping;
    this->m_NumBones = modX.m_NumBones;
    this->pos = pos;
    this->dimensions = modX.dimensions;
    this->startTime = GetCurrentTimeMillis();
}
*/
void AssimpModel::setPos(glm::vec3 pos)
{
    this->pos = pos;
}
void AssimpModel::setFaceDir(glm::vec3 faceDirection)
{
    this->faceDirection = this->faceDirection;
}

glm::vec3 AssimpModel::getBaseSize()
{
    return this->dimensions;
}
void AssimpModel::setSizeIncrease(float inc)
{
    this->sizeIncrease = glm::vec3(inc);
}
// draws the model, and thus all its meshes
void AssimpModel::Draw(Shader *shader)
{
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
    }
    passedTime = (GetCurrentTimeMillis()-this->startTime)/1000.0f;
    this->BoneTransform(passedTime);
    for(int i = this->Transforms.size(); i--;)
    {
        /*for(int a=0;a<4;a++){
            for(int b=0;b<4;b++){
                std::cout<<Transforms[i][b][a]<<"  ";
            }
            std::cout<<std::endl;
        }*/
        if(i < 100)
        {
            index=std::to_string(i);
            onePart = "gBones[";
            secondPart = "]";
            shader->setMat4(this->Transforms[i],(onePart+index.c_str()+secondPart).c_str());
        }
        else
        {
            std::cout<<"Too many bones: bone - "<<i<<std::endl;
        }
    }
    this->modelMat = glm::mat4(1.0);
    this->modelMat = glm::translate(this->modelMat,this->pos);
    //this->modelMat = getRotation(this->modelMat, this->pos, otherPos);
    this->modelMat = glm::rotate(this->modelMat,(float)glm::radians(-90.0),glm::vec3(1.0,0.0,0.0));
    this->modelMat = glm::scale(this->modelMat,this->sizeIncrease);
    shader->setMat4(this->modelMat,"modelMatrix");
    shader->use();
    for(int m = meshes.size(); m--;)
    {
        meshes[m]->Draw(shader);
    }
}

void AssimpModel::getPlayerRotation(glm::vec3 faceDir, glm::vec3 originFaceDir)
{
    float angle = acos(((glm::dot(glm::vec3(faceDir.x,0.0,faceDir.z), originFaceDir))/(sqrt(faceDir.x*faceDir.x+faceDir.z*faceDir.z)+1)));
    std::cout<<glm::degrees(angle)<<std::endl;
    this->modelMat = glm::rotate(this->modelMat, angle,glm::vec3(0.0,1.0,0.0));
}

int AssimpModel::FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    assert(pNodeAnim->mNumPositionKeys > 0);

    for(int i = 0; i < pNodeAnim->mNumPositionKeys - 1 ; i++)
    {
        if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime)
        {
            return i;
        }
    }

    assert(0);
}

int AssimpModel::FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    assert(pNodeAnim->mNumRotationKeys > 0);

    for(int i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++)
    {
        if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime)
        {
            return i;
        }
    }

    assert(0);
}

int AssimpModel::FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    assert(pNodeAnim->mNumScalingKeys > 0);

    for(int i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++)
    {
        if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime)
        {
            return i;
        }
    }

    assert(0);
}

const aiNodeAnim* AssimpModel::FindNodeAnim(const aiAnimation* pAnimation, aiNode* pNode)
{
    std::string nodeName = std::string(pNode->mName.data);
    for(int i = 0; i<pAnimation->mNumChannels; i++)
    {
        const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];
        if (std::string(pNodeAnim->mNodeName.data) == nodeName)
        {
            return pNodeAnim;
        }
    }

    return NULL;
}

void AssimpModel::CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    if (pNodeAnim->mNumPositionKeys == 1)
    {
        Out = pNodeAnim->mPositionKeys[0].mValue;
        return;
    }

    int PositionIndex = FindPosition(AnimationTime, pNodeAnim);
    int NextPositionIndex = (PositionIndex + 1);
    assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
    float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
    float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
    const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
    aiVector3D Delta = End - Start;
    Out = Start + Factor * Delta;
}

void AssimpModel::CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    // we need at least two values to interpolate...
    if (pNodeAnim->mNumRotationKeys == 1)
    {
        Out = pNodeAnim->mRotationKeys[0].mValue;
        return;
    }

    int RotationIndex = FindRotation(AnimationTime, pNodeAnim);
    int NextRotationIndex = (RotationIndex + 1);
    assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
    float DeltaTime = (float)pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime;
    float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
    const aiQuaternion& EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
    aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
    Out = Out.Normalize();
}

void AssimpModel::CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    if (pNodeAnim->mNumScalingKeys == 1)
    {
        Out = pNodeAnim->mScalingKeys[0].mValue;
        return;
    }
    int ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
    int NextScalingIndex = (ScalingIndex + 1);
    assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
    float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
    float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
    const aiVector3D& End   = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
    aiVector3D Delta = End - Start;
    Out = Start + Factor * Delta;
}
void AssimpModel::ReadNodeHeirarchy(float AnimationTime, aiNode* pNode, glm::mat4 ParentTransform)
{
    const aiAnimation* pAnimation = this->scene->mAnimations[0];
    glm::mat4 NodeTransformation = glm::mat4(1.0);
    const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, pNode);
    if (2==1)
    {
        this->modelMat = glm::mat4(1.0);
        // Interpolate translation and generate translation transformation matrix
        aiVector3D Translation;
        CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
        this->modelMat = glm::translate(this->modelMat,glm::vec3(Translation.x, Translation.y, Translation.z));
        NodeTransformation *= this->modelMat;

        // Interpolate rotation and generate rotation transformation matrix
        aiQuaternion RotationQ;
        CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);
        this->modelMat = getAssimp3f(RotationQ.GetMatrix());
        NodeTransformation *= this->modelMat;

        this->modelMat = glm::mat4(1.0);
        // Interpolate scaling and generate scaling transformation matrix
        aiVector3D Scaling;
        CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
        this->modelMat = glm::scale(this->modelMat,glm::vec3(Scaling.x, Scaling.y, Scaling.z));
        NodeTransformation *= this->modelMat;
        /*std::cout<<"Animate: "<<std::endl;
        for(int a = 0; a<4; a++)
        {
            for(int b = 0; b<4; b++)
            {
                std::cout<<NodeTransformation[b][a]<<"  ";
            }
            std::cout<<std::endl;
        }*/
    }
    else
    {
        NodeTransformation = getAssimp4f(pNode->mTransformation);
        /*std::cout<<"default: "<<std::endl;
        for(int a = 0; a<4; a++)
        {
            for(int b = 0; b<4; b++)
            {
                std::cout<<NodeTransformation[b][a]<<"  ";
            }
            std::cout<<std::endl;
        }*/
    }
    glm::mat4 GlobalTransformation = ParentTransform * NodeTransformation;

    if (m_BoneMapping.find(pNode->mName.data) != m_BoneMapping.end())
    {
        int BoneIndex = m_BoneMapping[pNode->mName.data];
        this->Transforms[BoneIndex] = globalInverseTransform * GlobalTransformation * boneOffset[BoneIndex];
        /*std::cout<<"Final: "<<std::endl;
        for(int a = 0; a<4; a++)
        {
            for(int b = 0; b<4; b++)
            {
                std::cout<<this->Transforms[BoneIndex][b][a]<<"  ";
            }
            std::cout<<std::endl;
        }*/
    }
    for (int n = pNode->mNumChildren; n--;)
    {
        ReadNodeHeirarchy(AnimationTime, pNode->mChildren[n], GlobalTransformation);
    }
}

void AssimpModel::BoneTransform(float TimeInSeconds)
{
    float TicksPerSecond = this->scene->mAnimations[0]->mTicksPerSecond != 0 ?
                           this->scene->mAnimations[0]->mTicksPerSecond : 25.0f;
    //std::cout<<TicksPerSecond<<std::endl;
    float TimeInTicks = TimeInSeconds * TicksPerSecond;
    float AnimationTime = fmod(TimeInTicks, this->scene->mAnimations[0]->mDuration);
    this->Transforms.resize(m_NumBones);
    ReadNodeHeirarchy(AnimationTime, this->scene->mRootNode, glm::mat4(1.0));
}

// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes std::vector.
void AssimpModel::loadModel(std::string &path)
{
    // read file via ASSIMP
    this->scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    if(!this->scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !this->scene->mRootNode) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    else
    {
        globalInverseTransform = getAssimp4f(this->scene->mRootNode->mTransformation);
        globalInverseTransform = glm::inverse(globalInverseTransform);
        for(int i = this->scene->mNumMeshes ; i--;)
        {

            this->verticesNr += scene->mMeshes[i]->mNumVertices;
        }
        this->bones.resize(this->verticesNr);
    }
    // retrieve the directory path of the filepath
    this->directory = path.substr(0, path.find_last_of('/'));

    // process ASSIMP's root node recursively
    processNode(this->scene->mRootNode);
}

// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
void AssimpModel::processNode(aiNode *node)
{
    //std::cout<<node->mName.data<<std::endl;
    // process each mesh located at the current node
    for(int m = node->mNumMeshes; m--;)
    {
        // the node object only contains indices to index the actual objects in the scene.
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = this->scene->mMeshes[node->mMeshes[m]];
        meshes.push_back(processMesh(mesh));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for(int n = node->mNumChildren; n--;)
    {
        processNode(node->mChildren[n]);
    }
}

void AssimpModel::loadBones(const aiMesh* pMesh)
{
    std::cout<<"bones: "<<pMesh->mNumBones<<std::endl;
    for (int b = 0; b < pMesh->mNumBones; b++)
    {
        int BoneIndex = 0;
        std::string BoneName(pMesh->mBones[b]->mName.data);
        if (m_BoneMapping.find(BoneName) == m_BoneMapping.end())
        {
            BoneIndex = m_NumBones;
            m_NumBones++;
            boneOffset.push_back(glm::mat4(1.0));
            boneOffset[BoneIndex] = getAssimp4f(pMesh->mBones[b]->mOffsetMatrix);
            m_BoneMapping[BoneName] = BoneIndex;
        }
        else
        {
            BoneIndex = m_BoneMapping[BoneName];
        }
        for (int v = 0; v<pMesh->mBones[b]->mNumWeights; v++)
        {
            int VertexID = pMesh->mBones[b]->mWeights[v].mVertexId;
            float Weight = pMesh->mBones[b]->mWeights[v].mWeight;
            bones[VertexID].addBoneData(BoneIndex, Weight);
        }

    }
}

AssimpMesh* AssimpModel::processMesh(aiMesh *mesh)
{
    loadBones(mesh);
    // data to fill
    std::vector<basicVertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture*> textures;

    basicVertex vertex;
    glm::vec3 vect;
    glm::vec2 vec;
    aiFace face;

    // walk through each of the mesh's vertices
    for(int i = 0; i<mesh->mNumVertices; i++)
    {
        // positions
        if(mesh->mVertices[i].x>this->edges[0])
        {
            this->edges[0]=mesh->mVertices[i].x;
        }
        if(mesh->mVertices[i].x<this->edges[1])
        {
            this->edges[1]=mesh->mVertices[i].x;
        }
        if(mesh->mVertices[i].y>this->edges[4])
        {
            this->edges[4]=mesh->mVertices[i].y;
        }
        if(mesh->mVertices[i].y<this->edges[5])
        {
            this->edges[5]=mesh->mVertices[i].y;
        }
        if(mesh->mVertices[i].z>this->edges[2])
        {
            this->edges[2]=mesh->mVertices[i].z;
        }
        if(mesh->mVertices[i].z<this->edges[3])
        {
            this->edges[3]=mesh->mVertices[i].z;
        }
        vect.x = mesh->mVertices[i].x;
        vect.y = mesh->mVertices[i].y;
        vect.z = mesh->mVertices[i].z;
        vertex.pos = vect;
        // normals
        vect.x = mesh->mNormals[i].x;
        vect.y = mesh->mNormals[i].y;
        vect.z = mesh->mNormals[i].z;
        vertex.norm = vect;
        // texture coordinates
        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.textr = vec;
        }
        else
            vertex.textr = glm::vec2(0.0f, 0.0f);
        /* // tangent
         std::vector.x = mesh->mTangents[i].x;
         std::vector.y = mesh->mTangents[i].y;
         std::vector.z = mesh->mTangents[i].z;
         vertex.Tangent = std::vector;
         // bitangent
         std::vector.x = mesh->mBitangents[i].x;
         std::vector.y = mesh->mBitangents[i].y;
         std::vector.z = mesh->mBitangents[i].z;
         vertex.Bitangent = std::vector;*/
        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    /*for(int i = mesh->mNumFaces; i--;)
    {
        face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices std::vector
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }*/
    // process materials
    aiMaterial* material = this->scene->mMaterials[mesh->mMaterialIndex];

    // 1. diffuse maps
    std::vector<Texture*> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    std::vector<Texture*> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Texture*> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Texture*> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    // return a mesh object created from the extracted mesh data
    AssimpMesh* daMesh = new AssimpMesh(vertices, indices, textures, this->bones);
    return daMesh;

}

// checks all material textures of a given type and loads the textures if they're not loaded yet.
// the required info is returned as a Texture struct.
std::vector<Texture*> AssimpModel::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture*> textures;
    for(int i = mat->GetTextureCount(type); i--;)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for(int j = 0; j < textures_loaded.size(); j++)
        {
            if(std::strcmp(textures_loaded[j]->getPath(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if(!skip)
        {
            // if texture hasn't been loaded already, load it
            //std::string fileName = std::string(str);
            Texture* texture = new Texture(str.C_Str(),GL_TEXTURE_2D,i,typeName);
            textures.push_back(texture);
            textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
    return textures;
}
