#include "../Inc/Mesh.h"
AssimpMesh::AssimpMesh(std::vector<basicVertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures, std::vector<boneData> bones)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
        this->bones = bones;
        setupMesh();
    }

    std::vector<basicVertex> AssimpMesh::getVert()
    {
        return this->vertices;
    }

    // render the mesh
    void AssimpMesh::Draw(Shader *shader)
    {
        // bind appropriate textures
        unsigned int diffuseNr  = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr   = 1;
        unsigned int heightNr   = 1;

        for(int i = textures.size(); i--;)
        {
            glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = textures[i]->getTyp();
            if(name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if(name == "texture_specular")
                number = std::to_string(specularNr++); // transfer unsigned int to stream
            else if(name == "texture_normal")
                number = std::to_string(normalNr++); // transfer unsigned int to stream
            else if(name == "texture_height")
                number = std::to_string(heightNr++); // transfer unsigned int to stream

            // now set the sampler to the correct texture unit
            glUniform1i(glGetUniformLocation(shader->id, (name + number).c_str()), i);
            // and finally bind the texture
            glBindTexture(GL_TEXTURE_2D, textures[i]->getId());
        }
        // draw mesh
        glBindVertexArray(this->VAO);
        glDrawArrays(GL_TRIANGLES, 0,this->vertices.size());
        glBindVertexArray(0);

        // always good practice to set everything back to defaults once configured.
        glActiveTexture(GL_TEXTURE0);
    }

    void AssimpMesh::setupMesh()
    {
        // create buffers/arrays
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &boneVBO);

        glBindVertexArray(VAO);
        // load data into basicVertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // A great thing about structs is that their memory layout is sequential for all its items.
        // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
        // again translates to 3/2 floats which translates to a byte array.
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(basicVertex), &this->vertices[0], GL_STATIC_DRAW);
        // set the basicVertex attribute pointers
        // basicVertex Positions
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(basicVertex), (void*)0);
        glEnableVertexAttribArray(0);
        // basicVertex texture coords
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(basicVertex), (void*)offsetof(basicVertex, textr));
        glEnableVertexAttribArray(1);
        // basicVertex normals
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(basicVertex), (void*)offsetof(basicVertex, norm));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, boneVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(bones[0]) * bones.size(), &bones[0], GL_STATIC_DRAW);
        glVertexAttribIPointer(3, 4, GL_INT, sizeof(boneData), (const GLvoid*)0);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(boneData), (void*)offsetof(boneData, weights));
        glEnableVertexAttribArray(4);

        glBindVertexArray(0);
    }
