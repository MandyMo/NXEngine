#version 410 core

in float EyeSize;
out vec4 FragColor;
uniform sampler2D  TexSprite;

void main(){
    FragColor = texture(TexSprite, gl_PointCoord) + EyeSize;
}