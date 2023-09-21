#include "SkyboxRenderer.h"

#include "../Camera.h"

#include <iostream>

SkyboxRenderer::SkyboxRenderer()
{
    std::cout<<"SkyboxSetupDebug1"<<std::endl;
    constexpr GLfloat SIZE = 500;
    std::vector<GLfloat> vertexCoords{
        // Back
        SIZE,
        -SIZE,
        -SIZE,
        -SIZE,
        -SIZE,
        -SIZE,
        -SIZE,
        SIZE,
        -SIZE,
        SIZE,
        SIZE,
        -SIZE,

        // Front
        -SIZE,
        -SIZE,
        SIZE,
        SIZE,
        -SIZE,
        SIZE,
        SIZE,
        SIZE,
        SIZE,
        -SIZE,
        SIZE,
        SIZE,

        // Right
        SIZE,
        -SIZE,
        SIZE,
        SIZE,
        -SIZE,
        -SIZE,
        SIZE,
        SIZE,
        -SIZE,
        SIZE,
        SIZE,
        SIZE,

        // Left
        -SIZE,
        -SIZE,
        -SIZE,
        -SIZE,
        -SIZE,
        SIZE,
        -SIZE,
        SIZE,
        SIZE,
        -SIZE,
        SIZE,
        -SIZE,

        // Top
        -SIZE,
        SIZE,
        SIZE,
        SIZE,
        SIZE,
        SIZE,
        SIZE,
        SIZE,
        -SIZE,
        -SIZE,
        SIZE,
        -SIZE,

        // Bottom
        -SIZE,
        -SIZE,
        -SIZE,
        SIZE,
        -SIZE,
        -SIZE,
        SIZE,
        -SIZE,
        SIZE,
        -SIZE,
        -SIZE,
        SIZE,
    };

    std::vector<GLuint> indices{0,  1,  2,  2,  3,  0,

                                4,  5,  6,  6,  7,  4,

                                8,  9,  10, 10, 11, 8,

                                12, 13, 14, 14, 15, 12,

                                16, 17, 18, 18, 19, 16,

                                20, 21, 22, 22, 23, 20};
    std::cout<<"SkyboxSetupDebug2"<<std::endl;
    m_skyCube.genVAO();
    std::cout<<"SkyboxSetupDebug3"<<std::endl;
    m_skyCube.addVBO(3, vertexCoords);
    std::cout<<"SkyboxSetupDebug4"<<std::endl;
    m_skyCube.addEBO(indices);
    std::cout<<"SkyboxSetupDebug5"<<std::endl;
    m_cubeTexture.loadFromFiles({
        "dm",
        "dm",
        "dt",
        "db",
        "dm",
        "dm",
    });
    std::cout<<"SkyboxSetupDebug6"<<std::endl;
}

void SkyboxRenderer::render(const Camera &camera)
{
    m_shader.useProgram();
    m_skyCube.bindVAO();
    m_cubeTexture.bindTexture();

    m_shader.loadViewMatrix(camera.getViewMatrix());
    m_shader.loadProjectionMatrix(camera.getProjMatrix());

    GL::drawElements(m_skyCube.getIndicesCount());
}
