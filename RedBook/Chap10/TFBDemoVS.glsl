#version 410 core

layout (location = 0) in vec3 vPosition;

out vec4 TPosition;
out vec4 XPosition;
uniform mat4 MVP;

void main(){
    if(vPosition.z >= 0 && vPosition.z <= 100){
        gl_Position = vec4(vPosition, 1.0f);
    }else{
        gl_Position = MVP * vec4(vPosition, 1.0f);
    }
    TPosition   = gl_Position;
    TPosition /= TPosition.w;
    XPosition = TPosition * 10;
}