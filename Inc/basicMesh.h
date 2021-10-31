#ifndef BASICMESH_H_INCLUDED
#define BASICMESH_H_INCLUDED

class basicMesh {
  public:
    ChunkMesh() = default;

    void addFace(const std::array<GLfloat, 12> &blockFace,
                 const std::array<GLfloat, 8> &textureCoords,
                 const sf::Vector3i &chunkPosition,
                 const sf::Vector3i &blockPosition, GLfloat cardinalLight);

    void bufferMesh();

    const Model &getModel() const;

    void deleteData();

    int faces = 0;

  private:
    GLuint VAO;
    GLuint VBO;
    std::vector<basicVertex> vertices;
    GLuint m_indexIndex = 0;
};

#endif // BASICMESH_H_INCLUDED
