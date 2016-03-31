#version 410 core


layout (location = 0) in vec2 vPosition;
layout (location = 1) in vec2 vUV;


out vec2 UV;

void main(){
    gl_Position = vec4(vPosition, 1.0f, 1.0f);
    UV          = vUV;
}