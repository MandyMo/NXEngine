#version 410 core

in vec3 Position;
out vec4 Color;

uniform samplerCube CubeTex;

void main(){
    Color = texture(CubeTex, Position);
}