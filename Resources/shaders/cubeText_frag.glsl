#version 440

in vec3 textCo;
uniform samplerCube cubText;
out vec4 daColor;

void main(){
   daColor = texture(cubText,textCo);
}
