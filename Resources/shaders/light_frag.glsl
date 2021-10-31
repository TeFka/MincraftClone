#version 440
//layout(depth_greater) out float gl_FragDepth;
in VS{
vec3 position;
vec3 color;
vec2 textcoord;
vec3 normal;
} fs;

layout(std140) uniform lightInf{
 float lCutOff;
 float lOuterCutOff;
 float lightConst;
 float lightLinear;
 float lightQuadr;
 vec3 camPos;
 vec3 camFront;
 vec3 lightPos1;
 vec3 lightPos2;
 vec3 lightPos3;
 vec3 lightPos4;
 vec3 lAmbient;
 vec3 lDiff;
 vec3 lSpec;
};
out vec4 fs_color;

uniform sampler2D textureA;
uniform float reflecG;
uniform vec3 mAmbient;
uniform vec3 mDiff;
uniform vec3 mSpec;
uniform float mShinin;

vec3 norma(vec3 nomb){
    return nomb/sqrt(pow(nomb.x,2)+pow(nomb.y,2)+pow(nomb.z,2));
}

vec3 calcLight(vec3 lPos, vec3 norml, vec3 fragPos, vec3 camPos){
   float lDistance = length(lPos-fragPos);
   float attenuation = 1.0/(lightConst+lightLinear*lDistance+lightQuadr*lDistance*lDistance);

   //Light
   vec3 ambLight = mAmbient*mDiff*0.3;
   //Difuse light
   vec3 norm = norma(norml);
   vec3 posToLightVec = norma(lPos-fragPos);
   vec3 lightColor = vec3(1.0,1.0,1.0);
   float diff = max(dot(posToLightVec, norm),0.0);
   vec3 diffFinal = lDiff*diff;
   //Specular light
   float lightPower = 1.0;
   vec3 reflectVec = reflect(posToLightVec, norm);
   vec3 viewToPosVec =  norma(camPos-fragPos);
   vec3 halfVec = norma(viewToPosVec+posToLightVec);
   float specularConst = pow(max(dot(norm,halfVec),0.0),64);
   vec3 specFinal = lSpec*(specularConst*mSpec);

   ambLight*=attenuation;
   diffFinal*=attenuation;
   specFinal*=attenuation;

   return (ambLight+diffFinal+specFinal);
}
float near = 0.1;
float far = 100;
//depth
float nLinearDep(float depth){
   float z = depth * 2-1.0;
   float dep = (2*far*near)/(far+near-z*(far-near));
   return dep;
}

void main(){
   vec3 norm = norma(fs.normal);
   vec3 result = calcLight(lightPos1,norm,fs.position,camPos);
   result += calcLight(lightPos2,norm,fs.position,camPos);
   result += calcLight(lightPos3,norm,fs.position,camPos);
   result += calcLight(lightPos4,norm,fs.position,camPos);

   float flash = 1.0;
   vec3 posToCamVec = norma(fs.position-camPos);
   float theta = dot(posToCamVec,norma(camFront));
   float epsilon = lCutOff - lOuterCutOff;
   float intensity = clamp((theta - lOuterCutOff) / epsilon, 0.0, 1.0);

   fs_color = texture(textureA, fs.textcoord)*vec4(result,1.0);
}
