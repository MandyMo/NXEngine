#version 330 core

layout(location = 0) in vec2 vPosition;
layout(location = 1) in vec4 vColor;

out vec4 Color;
void main(){
    gl_Position = vec4(vPosition, -0.5f, 1.0f);
    Color       = vColor;
}