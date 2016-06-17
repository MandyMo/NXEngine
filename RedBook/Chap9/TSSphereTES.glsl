#version 410 core

layout(quads, equal_spacing) in;

uniform mat4 MVP;
out vec3 Color;

const float PI = 3.1415926;

patch in vec3  bPosition;
patch in float bRadius;

void main(){
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;
    
    float phi    = PI * (u - 0.5f);
    float theta  = 2.0f * PI - (v - 0.5f);
    float cosphi = cos(phi);
    vec3 xyz = vec3(cosphi * cos(theta), sin(phi), cosphi * sin(theta));
    
    gl_Position = MVP * vec4(bRadius * xyz + bPosition, 1.0f);
}