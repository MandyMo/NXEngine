#version 410 core

 in vec4 iColor;
layout(location = 0)out vec4 vColor;
layout(location = 1)out vec4 xColor;
void main(){
    vColor = iColor;
    xColor = iColor / 2;
}