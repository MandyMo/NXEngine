#version 410 core

layout(isolines, equal_spacing) in;

uniform mat4 MVP;
out vec3 Color;

void main(){
    vec4 p0 = gl_in[0].gl_Position;
    vec4 p1 = gl_in[1].gl_Position;
    vec4 p2 = gl_in[2].gl_Position;
    vec4 p3 = gl_in[3].gl_Position;
    float u = gl_TessCoord.x;
    float b0 = pow(1 - u, 3);
    float b1 = 3 * u * pow(1 - u, 2);
    float b2 = 3 * u * u * (1 - u);
    float b3 = u * u * u;
    gl_Position = b0 * p0 + b1 * p1 + b2 * p2 + b3 * p3;
    gl_Position.w = 1.0f;
    Color = gl_Position.xyz;
    gl_Position = MVP * gl_Position;
}