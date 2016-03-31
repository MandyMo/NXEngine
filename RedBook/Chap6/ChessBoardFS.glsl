#version 410 core

uniform sampler2D TexA;
in vec2 uv;
out vec4 Color;

void main(){
    Color = texture(TexA, uv);
}
