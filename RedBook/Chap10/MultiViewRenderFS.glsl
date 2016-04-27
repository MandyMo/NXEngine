#version 410 core

out vec4 FragColor;

void main(){
    FragColor = (gl_FragCoord + vec4(1)) / 2;
}