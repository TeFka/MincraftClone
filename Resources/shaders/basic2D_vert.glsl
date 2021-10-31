#version 440 core

layout(location=0) in vec2 vert;
layout(location=1) in vec2 textCoord;
layout(location=2) in vec4 col;
layout(location=3) in int textN;

uniform mat4 projectionMatrix;
out vec2 textCo;
flat out int textNr;
out vec4 color;

void main(){
   gl_Position = projectionMatrix*vec4(vert.xy,0.0,1.0);
   textCo = vec2(textCoord.x,textCoord.y*-1.0f);
   textNr = textN;
   color = col;
}
