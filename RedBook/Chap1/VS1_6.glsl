#version 410 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec4 vColor;
layout(location = 2) in vec2 uv;

uniform mat4x4 MVP;


out vec4 iColor;
out vec2 iuv;


void main(){
    iColor = vColor;
    gl_Position = MVP * vec4(vPosition, 1.0f);
    iuv         = uv;
}