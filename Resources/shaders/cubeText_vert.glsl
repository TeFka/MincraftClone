#version 440

layout(location=0) in vec3 aPos;

layout(std140) uniform matrixes{
    mat4 projectionMatrix;
};
out vec3 textCo;
uniform mat4 viewMatrix;

void main(){
    textCo = aPos;
    vec4 pas = projectionMatrix*viewMatrix*vec4(aPos,1.0);
    gl_Position= pas.xyww;
}
