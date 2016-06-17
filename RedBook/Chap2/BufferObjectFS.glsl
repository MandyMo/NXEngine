#version 410 core

in   vec4 Color;
out  vec4 FragColor;

subroutine vec4 GetColor(in vec4 color);

subroutine (GetColor) vec4 SelfColor(in vec4 color){
    return color;
}

subroutine (GetColor) vec4 HalfColor(in vec4 color){
    return color / 100.0f;
}

subroutine uniform GetColor ColorFunc;

void main(){
    FragColor = ColorFunc(Color);
}