#version 410 core

in vec4 Position;
out vec4 Color;

uniform sampler3D Tex;

void main(){
    vec3 SamplePosition = vec3(Position.x / Position.w, Position.y / Position.w, Position.z / Position.w);
    if(SamplePosition.x < 0){
        SamplePosition.x += 1;
    }
    if(SamplePosition.y < 0){
        SamplePosition.y += 1;
    }
    if(SamplePosition.z < 0){
        SamplePosition.z += 1;
    }
    Color = texture(Tex, SamplePosition);
}