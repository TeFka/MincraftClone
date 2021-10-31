#version 440

layout(triangles) in;
layout(triangle_strip,max_vertices = 3) out;

uniform float time;

in VS{
   vec3 pos;
   vec2 text;
   vec3 norm;
} gs[];

out VS{
   vec3 pos;
   vec2 text;
   vec3 norm;
} fs;

vec3 getNorm(){
   vec3 a = vec3(gl_in[0].gl_Position)-vec3(gl_in[1].gl_Position);
   vec3 b = vec3(gl_in[2].gl_Position)-vec3(gl_in[1].gl_Position);
   return normalize(cross(a,b));
}
vec4 explode(vec4 pos, vec3 norm){
    float magn = 8.0;
    vec3 dir = norm *((sin(time)+1.0)/2.0)*magn;
    return pos + vec4(dir,0.0);
}

void main(){
   vec3 norm = getNorm();
   gl_Position = gl_in[0].gl_Position;
   EmitVertex();
   gl_Position = gl_in[1].gl_Position;
   EmitVertex();
   gl_Position = gl_in[2].gl_Position;
   EmitVertex();
   EndPrimitive();
}
