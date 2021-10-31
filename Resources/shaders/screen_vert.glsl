#version 440

layout(location=0) in vec3 post;
layout(location=1) in vec2 texCo;

out vec2 textCoord;

void main(){
   gl_Position = vec4(post.x,post.y,0.0,1.0);
   textCoord = vec2(texCo.x,texCo.y);
}
