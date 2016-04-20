#version 410 core

layout (vertices = 3) out;

in vec2 MCposition[];
out vec2 MTPosition[];

void main(){
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    gl_TessLevelOuter[0] = 10;
    gl_TessLevelOuter[1] = 10;
    gl_TessLevelOuter[2] = 10;
    gl_TessLevelInner[0] = 10;
    MTPosition[gl_InvocationID] = MCposition[gl_InvocationID];
}