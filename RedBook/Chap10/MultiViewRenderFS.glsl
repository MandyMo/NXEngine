#version 410 core

out vec4 FragColor;
in vec4 gColor;
void main(){
    FragColor = gColor;
}