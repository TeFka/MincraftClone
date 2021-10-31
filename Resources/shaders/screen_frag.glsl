#version 440

in vec2 textCoord;

uniform sampler2D textr;
uniform float exposure;
uniform int mode;

uniform vec4 additionalCol;

out vec4 daColor;

const float offSet = 1/300.0;

void main()
{
    vec3 cor;
    if(mode==3){
     vec2 offS[9] = vec2[](
        vec2(-offSet,offSet),
        vec2(0.0,offSet),
        vec2(offSet,offSet),
        vec2(-offSet,0.0),
        vec2(0.0,0.0),
        vec2(offSet,0.0),
        vec2(-offSet,-offSet),
        vec2(0.0,-offSet),
        vec2(offSet,-offSet)
     );
     float kernels[9] = float[](
         1,2,1,
         2,4,2,
         1,2,1
     );
     //blur
     for(int i=0;i<9;i++){
         kernels[i]=kernels[i]/16;
     }
    vec3 sampleT[9];
    for(int i=0;i<9;i++){
       sampleT[i]=vec3(texture(textr,textCoord.st + offS[i]));
    }
    cor = vec3(0.0);

    for(int i=0;i<9;i++){
     cor += sampleT[i]*kernels[i];
    }
        float average = (cor.r+cor.g+cor.b)/3.0;
        cor = vec3(average,average,average);
    }
    else{
        cor = texture(textr,textCoord).rgb;
    }
    vec3 mapCor = vec3(1.0) - exp(-cor*exposure);
    daColor = vec4(mapCor,1.0)*additionalCol;
    if(mode>1)
    {

    }
    if(mode==1||mode==3)
    {

    }
}
