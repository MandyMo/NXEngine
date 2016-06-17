#version 410 core

layout (vertices = 4)out;

uniform int Outer = 5;

void main(){
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    
    gl_TessLevelOuter[0] = Outer;
    gl_TessLevelOuter[1] = Outer;
    gl_TessLevelOuter[2] = Outer;
    gl_TessLevelOuter[3] = Outer;
    
    gl_TessLevelInner[1] = Outer;
    gl_TessLevelInner[0] = Outer;
}