#version 440

layout(triangles) in;
layout(triangle_strip, max_vertices = 18) out;

uniform mat4 shadowMat[6];
out vec4 pos;

void main()
{
    for(int f = 0; f<6; ++f)
    {
        gl_Layer = f;
        for(int i = 0; i<3; ++i)
        {
            pos = gl_in[i].gl_Position;
            gl_Position = shadowMat[f]*pos;
            EmitVertex();
        }
        EndPrimitive();
    }
}
