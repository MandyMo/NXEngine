#version 410 core

uniform float Dif;
uniform sampler2D TexA;
uniform sampler2D TexB;

in vec2 UV;
out vec4 Color;

void main(){
    vec4 ColorA = texture(TexA, UV);
    vec4 ColorB = texture(TexB, vec2(UV.x + Dif, UV.y));
    Color = ColorA * ColorB;
}