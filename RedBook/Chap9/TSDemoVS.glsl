#version 410 core

layout (location = 0) in vec3 vPosition;

out vec2 MCposition;



void main(){
    gl_Position = vec4(vPosition, 1.0f);
    MCposition  = vPosition.xy;
}