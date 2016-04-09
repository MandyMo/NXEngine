#version 410 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vUV;

out vec2 UV;
out vec4 MVPosition;    //position in camera space


uniform mat4x4 MV;      //object -> camera
uniform mat4x4 MVP;     //object -> ndc

void main(){
    UV          = vUV;
    gl_Position = MVP * vec4(vPosition, 1.0f);
    MVPosition  = MV  * vec4(vPosition, 1.0f);
}