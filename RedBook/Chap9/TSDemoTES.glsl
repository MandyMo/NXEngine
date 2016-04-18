#version 410 core

layout (triangles) in;

in vec2 MTPosition[];

out vec2 Position;

uniform mat4 MVP;

void main(){
    float a = gl_TessCoord.x;
    float b = gl_TessCoord.y;
    float c = gl_TessCoord.z;
    gl_Position = gl_in[0].gl_Position * a + gl_in[1].gl_Position * b + gl_in[2].gl_Position * c;
    float x = abs(gl_Position.x), y = abs(gl_Position.y), z = abs(gl_Position.z);
    float len = sqrt(x * x + y * y +  z * z);
    gl_Position *= 400 / len;
    gl_Position.w = 1;
    gl_Position = MVP * gl_Position;
    Position  = MTPosition[0] * a + MTPosition[1] * b + MTPosition[2] * c;
}