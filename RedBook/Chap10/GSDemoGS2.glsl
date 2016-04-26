#version 410 core

layout (triangles) in;
layout (line_strip, max_vertices = 10) out;

void main(){
    for(int i = 0; i < gl_in.length(); ++i){
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();
    EndPrimitive();
}