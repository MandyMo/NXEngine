
#version 410 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in float vPointSize;



uniform mat4 MVP;

out float EyeSize;



void main(){
    gl_Position  = MVP * vec4(vPosition, 1.0f);
    EyeSize      = pow(gl_Position.z / gl_Position.w, 1);
    gl_PointSize =  64 * EyeSize;
}