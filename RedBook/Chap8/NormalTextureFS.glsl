#version 410 core

in vec2 UV;                  //UV
in vec4 MVPosition;          //position in camera space
out vec4 FragColor;          //fragment color


uniform vec4 LightDirection; //light direction
uniform mat4x4 MV;           //object -> camera
uniform mat4x4 MVP;          //object -> ndc
uniform sampler2D   Texture;
uniform sampler2D   Normal;

vec3 CaculateColor();
vec3 CaculateColor2();

void main(){
    //FragColor = vec4(CaculateColor(), 1.0f);
    FragColor = vec4(CaculateColor2(), 1.0f);
}

const vec3 Ambient  = vec3(0.1, 0.1, 0.1);
const vec3 Diffuse  = vec3(0.3, 0.3, 0.3);
const vec3 Specular = vec3(0.6, 0.6, 0.6);

vec3 CaculateColor2(){
    vec4 LightDir = MV * LightDirection;
    vec4 TexColor = texture(Texture, UV);
    vec4 XY = fract(MVPosition / 50);
    XY -= 0.5;
    XY.z = 0;
    XY.w = 0;
    XY.z = -sqrt(1 - dot(XY, XY));
    
    normalize(LightDir);
    
    vec4 EyeDir = -MVPosition;
    EyeDir.w = 0;
    normalize(EyeDir);
    
    vec4 Half = (EyeDir + -LightDir) / 2;
    normalize(Half);
    
    float DifFactor = clamp(-dot(LightDir, XY), 0, 1);
    
    float SpecFactor = clamp(dot(Half, XY), 0, 1);
    
    
    
    vec3 Module = Ambient + DifFactor * Diffuse;
    SpecFactor = 0;
    vec3 Color = clamp(Module * (texture(Texture, UV).xyz) + SpecFactor * Specular, 0.0f, 1.0f);
    return Color.xyz;
}


vec3 CaculateColor(){
    vec3 Color;
    vec4 NormalL   = MV * texture(Normal, UV);
    vec4 LightDir  = MV * LightDirection;
    float DifFactor = clamp(dot(LightDir, NormalL), 0.0f, 1.0f);
    vec3 Module = Ambient + DifFactor * Diffuse;
    
    vec3 Half = ((LightDir + NormalL) / 2).xyz;
    float SpecFactor = clamp(dot(Half, -MVPosition.xyz), 0.0f, 1.0f);
    
    Color = clamp(Module * (texture(Texture, UV).xyz) + SpecFactor * Specular, 0.0f, 1.0f);
    return Color;
}