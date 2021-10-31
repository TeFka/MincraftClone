#version 440

layout(location=0) in vec3 pos;
layout(location=1) in vec2 textr;
layout(location=2) in vec3 norm;

layout(std140) uniform matrixes{
mat4 projectionMatrix;
mat4 viewMatrix;
};

out VS{
   vec3 pos;
   vec2 textr;
   vec3 norm;
   vec4 lightMatrix;
} fs;

uniform mat4 modelMatrix;
uniform mat4 shadowmat;
uniform int normRev;

void main(){
   fs.pos = vec3(modelMatrix*vec4(pos,1.0));
   fs.textr = vec2(textr.x,textr.y*-1.0);
   fs.norm = transpose(inverse(mat3(modelMatrix)))*norm;
   fs.lightMatrix = shadowmat*vec4(fs.pos,1.0);
   if(normRev==1){
     fs.norm*=-1.0;
   }
   gl_Position = projectionMatrix*viewMatrix*modelMatrix*vec4(pos,1.0);
}
