#version 440

out vec4 daColor;

in VS
{
    vec3 pos;
    vec2 textr;
    vec3 norm;
    vec4 lightMatrix;
    float opacity;
} gs;

uniform vec4 lCol;
uniform int useText;
uniform sampler2D textare;
/*uniform samplerCube shadowMap;
uniform sampler2D shadowmap;
uniform int type;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float farP;
uniform float chosenBias;*/

/*float linearizeDepth(float zDepth)
{
    float zNear = 0.1;    // TODO: Replace by the zNear of your perspective projection
    float zFar  = farP; // TODO: Replace
    return (2.0 * zNear) / (zFar + zNear - zDepth * (zFar - zNear));
}

float shadowCalc(vec4 fragPosLightSpace, vec3 fPos, float bias, float offset)
{
    float pcfDepth;
    float currDepth;
    float inShadow = 0.0;
    vec3 fragToLight;
    vec3 projCoords;
    if(type==1)
    {
        fragToLight = fPos-lightPos;
        currDepth = length(fragToLight);
    }
    else
    {
        projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
        projCoords = projCoords * 0.5 + 0.5;
        currDepth = linearizeDepth(projCoords.z);
    }
    for(float x =-offset; x<offset; x+=offset)
    {
        for(float y=-offset; y<offset; y+=offset)
        {
            for(float z=-offset; z<offset; z+=offset)
            {
                if(type==1)
                {
                    pcfDepth = texture(shadowMap,fragToLight+vec3(x,y,z)).r;
                    pcfDepth*=farP;
                }
                else
                {
                    pcfDepth = linearizeDepth(texture(shadowmap,projCoords.xy).r);
                }
                if(currDepth-bias>pcfDepth)
                {
                    inShadow += 1.0;
                }
            }
        }
    }
    inShadow = inShadow/27;
    return inShadow;
}*/

void main()
{
    //lightning
    /*vec3 norm = normalize(gs.norm);
    vec3 lightCol=vec3(0.6);
    vec3 lDir = normalize(lightPos-gs.pos);
    float diff = max(dot(lDir,norm),0.0);
    vec3 finalDiff = diff*lightCol;
    vec3 viewDir = normalize(viewPos-gs.pos);
    float spec=0.0;
    vec3 halfDir = normalize(lDir+viewDir);
    spec = pow(max(dot(norm,halfDir),0.0),64.0);
    vec3 finalSpec = spec*lightCol;
    float bias = max(0.05*(1.0-dot(norm,lDir)),0.005);
    float shadow = shadowCalc(gs.lightMatrix,gs.pos, chosenBias, 0.1);*/
    vec4 col;
    //base
    if(useText==1){
        vec3 textur = texture(textare,gs.textr).rgb;
        col = vec4(textur,gs.opacity);
    }
    else{
        col=lCol;
    }
    //vec3 ambient = vec3(0.2*col.rgb);
    //vec3 light = (ambient+(1.0-shadow)*(finalDiff+finalSpec))*lCol.rgb;
    daColor = col;
}

