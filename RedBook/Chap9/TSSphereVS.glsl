#version 410 core


layout (location = 0) in vec4 vPosition;

out vec3 Position;
out float Radius;


void main(){
    gl_Position = vec4(vPosition.xyz, 1.0f);
    Position = vPosition.xyz;
    Radius   = vPosition.w;
}