#version 410 core

layout (location = 0) in vec2 vPosition;
layout (location = 1) in vec2 vuv;

out vec2 uv;

void main(){
    uv = vuv;
    gl_Position = vec4(vPosition, 1.0f, 1.0f);
}