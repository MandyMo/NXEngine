#version 410 core

in vec3 Color;

out vec4 FragColor;
void main(){
    //float len = length(Color / 10);
    //FragColor = vec4(fract(len));
//    FragColor.g += 0.5;
    FragColor = vec4(0, 1, 0, 1);
}