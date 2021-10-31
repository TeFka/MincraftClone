#version 440

layout(location = 0) in vec3 pos;

uniform mat4 modelMatrix;
void main()
{
    gl_Position = modelMatrix*vec4(pos,1.0);
}
