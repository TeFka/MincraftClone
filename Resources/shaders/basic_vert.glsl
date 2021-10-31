#version 440

layout(location=0) in vec3 pos;
layout(location=1) in vec2 textr;
layout(location=2) in vec3 norm;
layout(location=3) in float opas;

layout(std140) uniform matrixes{
mat4 projectionMatrix;
mat4 viewMatrix;
};

out VS{
   vec3 pos;
   vec2 textr;
   vec3 norm;
   vec4 lightMatrix;
   float opacity;
} fs;

uniform mat4 shadowmat;
uniform int normRev;

void main(){
   fs.pos = pos;
   fs.textr = vec2(textr.x,textr.y*-1.0);
   fs.norm = norm;
   fs.lightMatrix = shadowmat*vec4(fs.pos,1.0);
   fs.opacity = opas;
   if(normRev==1){
     fs.norm*=-1.0;
   }
   gl_Position = projectionMatrix*viewMatrix*vec4(pos,1.0);
}
