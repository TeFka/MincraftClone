#version 440
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec2 vertex_textcoord;
layout (location = 2) in vec3 vertex_normal;

layout (std140) uniform matrixes{
    mat4 projectionMatrix;
    mat4 viewMatrix;
};

out VS{
vec3 position;
vec2 textcoord;
vec3 normal;
} vs;

uniform mat4 modelMatrixAr[7];


void main(){
  mat4 modelMatrix = modelMatrixAr[gl_InstanceID];
  gl_Position = projectionMatrix*viewMatrix*modelMatrix*vec4(vertex_position, 1.f);
  vs.position = vec3(modelMatrix*vec4(vertex_position,1.0));
  vs.textcoord = vec2(vertex_textcoord.x, vertex_textcoord.y*-1.f);
  vs.normal = mat3(transpose(inverse(modelMatrix)))*vertex_normal;


}
