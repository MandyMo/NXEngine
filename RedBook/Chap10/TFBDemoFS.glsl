#version 410 core

in vec4 TPosition;

out vec4 FragColor;

void main(){
    FragColor = TPosition;
    FragColor /= TPosition.w;
    FragColor = (FragColor + vec4(1)) / 2;
    //FragColor.a = 1.0f;
}