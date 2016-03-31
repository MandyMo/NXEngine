#version 410 core

in vec4 iColor;
out vec4 vColor;
in vec2 iuv;

uniform sampler2D text;

void main(){
    vec4 texColor = texture(text, iuv);
    vColor = texColor;// * iColor;
}