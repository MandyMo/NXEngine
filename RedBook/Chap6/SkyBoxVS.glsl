#version 410 core

layout(location = 0) in vec3 vPosition;
out vec3 Position;

uniform mat4 MVP;

void main(){
    gl_Position = vec4(vPosition, 1.0f);
    gl_Position = MVP * gl_Position;
    Position    = vPosition;
}