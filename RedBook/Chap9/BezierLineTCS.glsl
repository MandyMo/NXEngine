#version 410 core

layout (vertices = 4) out;

uniform int Outer;

void main(){
    for(int i = 0; i < gl_PatchVerticesIn; ++i){
        gl_out[i].gl_Position = gl_in[i].gl_Position;
    }
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    gl_TessLevelOuter[0] = 5;
    gl_TessLevelOuter[1] = Outer;
}