#version 440
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in ivec4 BoneIDs;
layout (location = 4) in vec4 Weights;

out vec2 TexCoords;

layout (std140) uniform matrixes
{
    mat4 projectionMatrix;
    mat4 viewMatrix;
};

uniform mat4 modelMatrix;
uniform mat4 gBones[100];

void main()
{
    TexCoords = aTexCoords;

    mat4 BoneTransform = gBones[BoneIDs[0]] * Weights[0];
    BoneTransform += gBones[BoneIDs[1]] * Weights[1];
    BoneTransform += gBones[BoneIDs[2]] * Weights[2];
    BoneTransform += gBones[BoneIDs[3]] * Weights[3];
    vec4 PosL = BoneTransform * vec4(aPos, 1.0);
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * PosL;
}
