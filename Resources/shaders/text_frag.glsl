#version 440 core
in vec2 TexCoords;
out vec4 color;
uniform sampler2D textr;
uniform vec3 textCol;
void main()
{
vec4 sampled = vec4(1.0, 1.0, 1.0, texture(textr, TexCoords).r);
color = vec4(textCol, 1.0) * sampled;
}
