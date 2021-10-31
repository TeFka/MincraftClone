#version 440

//out vec4 daColor;
layout(location = 0) out float gl_FragDepth;
in vec4 pos;
uniform vec3 lightPos;
uniform float farP;

void main()
{
    float lightDistance;

    lightDistance = length(pos.xyz-lightPos);
    lightDistance = lightDistance/farP;
    gl_FragDepth = lightDistance;
}
