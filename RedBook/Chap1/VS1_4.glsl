#version 410 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec4 vColor;

 out vec4 iColor;
uniform mat4x4 MVP;

void main(){
    iColor = vColor;
    gl_Position = MVP * vec4(vPosition, 1.0f);
}