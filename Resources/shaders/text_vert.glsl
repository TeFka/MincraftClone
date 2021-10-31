#version 440 core
layout (location = 0) in vec4 vert;
//layout (location = 1) in vec2 textr;

uniform mat4 projectionMatrix;
out vec2 TexCoords;
void main()
{
    gl_Position = projectionMatrix*vec4(vert.xy, 0.1, 1.0);
    TexCoords = vert.zw;
}
