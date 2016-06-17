#version 410 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec2 Position[];
out vec2 MCPosition;

void main(){
    for(int n = 0; n < 3; ++n){
        gl_Position = gl_in[n].gl_Position;
        MCPosition = Position[n];
        EmitVertex();
    }
    EndPrimitive();
}