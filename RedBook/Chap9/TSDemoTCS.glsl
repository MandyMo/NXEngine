#version 410 core

layout (vertices = 4) out;

in vec2 MCposition[];
out vec2 MTPosition[];

void main(){
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    gl_TessLevelOuter[0] = 1;
    gl_TessLevelOuter[1] = 2;
    gl_TessLevelOuter[2] = 3;
    gl_TessLevelOuter[3] = 4;
    gl_TessLevelInner[0] = 2;
    gl_TessLevelInner[1] = 2;
    MTPosition[gl_InvocationID] = MCposition[gl_InvocationID];
}