#version 410 core

layout (location = 0) in vec4 vPosition;
out vec4 Position;

uniform mat4x4  MVP;

void main(){
    gl_Position = MVP * vPosition;
    Position    = gl_Position;
}