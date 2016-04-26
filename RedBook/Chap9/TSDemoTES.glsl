#version 410 core

layout (quads) in;

in vec2 MTPosition[];

out vec2 Position;

uniform mat4 MVP;

void main(){
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;
    
    vec4 p0 = gl_in[0].gl_Position;
    vec4 p1 = gl_in[1].gl_Position;
    vec4 p2 = gl_in[2].gl_Position;
    vec4 p3 = gl_in[3].gl_Position;
    
    vec4 a = p0 * (1 - u) + p2 * u;
    vec4 b = p1 * (1 - u) + p3 * u;
    
    gl_Position = a * (1 - v) + b * v;
    
    gl_Position.w = 1;
    gl_Position = MVP * gl_Position;
    Position  = MTPosition[0];
}