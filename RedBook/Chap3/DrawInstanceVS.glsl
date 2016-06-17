#version 410 core

layout (location = 0) in vec3 vPosition;

//instance attrib
layout (location = 1) in vec3 vColor;
layout (location = 2) in vec2 vDif;

out vec3 Color;

void main(){
    gl_Position = vec4(vPosition.x + vDif.x, vPosition.y + vDif.y, vPosition.z, gl_InstanceID + 1);
    Color       = vec3(1.0f, 0.0f, 0.0f) * 1.0f / (gl_InstanceID + 1);
}