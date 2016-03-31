#version 410 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;

out vec4 Color;


void main(){
    gl_Position = vec4(vPosition, 1.0);
    Color       = vec4(vColor, 1.0);
}

