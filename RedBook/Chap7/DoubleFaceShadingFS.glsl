#version 410 core

in   vec4 Color;
out  vec4 FragColor;

vec4 GetColor(){
    if(gl_FrontFacing){
        return Color;
    }else{
        return Color / 2.0f;
    }
}


void main(){
    FragColor = GetColor();
}