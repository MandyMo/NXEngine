#version 410 core

layout(triangles, invocations = 4) in;
layout(triangle_strip, max_vertices = 10) out;

void main(){
    for(int i = 0; i < gl_in.length(); ++i){
        gl_ViewportIndex = gl_InvocationID;
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
}