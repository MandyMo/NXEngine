#version 410 core

uniform sampler2D TexA;
uniform sampler2D TexB;

in vec2 oUV;
out vec4 Color;

void main(){
    vec4 ColorA = texture(TexA, oUV);
    vec4 ColorB = texture(TexB, oUV);
    Color = ColorA + ColorB;
}