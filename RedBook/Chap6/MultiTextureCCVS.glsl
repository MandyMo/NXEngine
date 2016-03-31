#version 410 core

in vec3 Position;
in vec2 UV;
out vec2 oUV;

uniform mat4 MVP;

void main(){
    gl_Position = MVP * vec4(Position, 1.0f);
    oUV         = UV;
}