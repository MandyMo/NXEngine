#version 410 core

out vec4 FragColor;
in vec4 gColor;
void main(){
    FragColor = gl_FragCoord;
    FragColor /= FragColor.z;
    FragColor.w = 1.0f;
    FragColor = (FragColor + vec4(1)) / 2;
}