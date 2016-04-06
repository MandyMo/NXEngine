#version 410 core

in vec2 UV;
out vec4 FragColor;

uniform float Deleta;

void main(){
    vec2 uv = clamp(UV, 0, 1);
    float u = uv.s;
    float v = uv.t;
    if(v >= 0.5 - Deleta || v <= 0.5 + Deleta){
        FragColor = vec4(1);
    }else if(v < 0.5 - Deleta){
        if(u <= Deleta || u >= 1 - Deleta){
            FragColor = vec4(1);
        }else{
            FragColor = vec4(0);
        }
    }else{
        if(u <= 0.5 + Deleta && u >= 0.5 - Deleta){
            FragColor = vec4(1);
        }else{
            FragColor = vec4(0);
        }
    }
    //FragColor = vec4(0);
}