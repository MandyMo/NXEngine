#version 410 core

in vec2 UV;
uniform sampler2D SMP2D;

out vec4 Color;

void main(){
    Color = texture(SMP2D, UV);
}