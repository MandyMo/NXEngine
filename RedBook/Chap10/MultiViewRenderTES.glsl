#version 410 core

layout (quads, equal_spacing) in;


uniform mat4 MVP;

void main(){
    vec4 p0 = gl_in[0].gl_Position;
    vec4 p1 = gl_in[1].gl_Position;
    vec4 p2 = gl_in[2].gl_Position;
    vec4 p3 = gl_in[3].gl_Position;
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;
    vec4 PosA = (1 - v) * p0 + v * p3;
    vec4 PosB = (1 - v) * p1 + v * p2;
    gl_Position = (1 - u) * PosA + u * PosB;
    gl_Position.w = 1.0f;
    gl_Position = MVP * gl_Position;
}