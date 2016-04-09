#version 410 core


in vec2 MCposition;

out vec4 FragColor;

const vec2  BrickPct = vec2(0.1, 0.1);
const float LightIntensity = 1.0f;
const vec3  BrickColor  = vec3(0, 0, 0);
const vec3  MortarColor = vec3(1);
const vec2  BrickSize   = vec2(90, 90);
const float Deleta = 0.0125;


vec4 CaculateColor();

void main() {
    CaculateColor();
}

vec4 CaculateColor(){
    vec2 position = MCposition / BrickSize;
    float u = fract(position.x);
    float v = fract(position.y);
//    if(v >= 1- Deleta){
//        FragColor = vec4(1);
//    }else if (v <= Deleta){
//        FragColor = vec4(1);
//    }else if(v >= 0.5 - Deleta && v <= 0.5 + Deleta){
//        FragColor = vec4(1);
//    }else if(v < 0.5 - Deleta){
//        if(u <= Deleta || u >= 1 - Deleta){
//            FragColor = vec4(1);
//        }else{
//            FragColor = vec4(0);
//        }
//    }else{
//        if(u <= 0.5 + Deleta && u >= 0.5 - Deleta){
//            FragColor = vec4(1);
//        }else{
//            FragColor = vec4(0);
//        }
//    }
//    u -= 0.5;
//    v -= 0.5;
//    if(u*u + v * v >= 0.25){
//        FragColor = vec4(1);
//    }else{
//        FragColor = vec4(0);
//    }
    if(u >= 0.2 && v >= 0.2){
        FragColor = vec4(1);
    }else{
        discard;
    }
    return FragColor;
}