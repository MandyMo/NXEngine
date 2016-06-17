#version 410 core

layout (location = 0) in vec3 vPosition;

out vec2 MCposition;

uniform mat4 MVP;

void main(){
    gl_Position = MVP * vec4(vPosition, 1.0f);
    MCposition  = vPosition.xy;
}