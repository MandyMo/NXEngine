#version 410 core

in vec3 Color;

out vec4 ColorA;
out vec4 ColorB;
void main(){
   ColorA = vec4(Color, 0.5f);
   ColorB = vec4(Color/2, 1.0f);
}