#version 410 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vUV;

out vec2 UV;

uniform mat4 MVP;

void main(){
    gl_Position = MVP * vec4(vPosition, 1.0f);
    UV          = vUV;
}