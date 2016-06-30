#version 400

layout (vertices = 1) out;

in vec3 Position[];
in float Radius[];

patch out vec3  bPosition;
patch out float bRadius;

uniform int Outer;

void main(){
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    gl_TessLevelOuter[0] = (bRadius + 20) / 20 + 4;
    gl_TessLevelOuter[1] = gl_TessLevelOuter[0];
    gl_TessLevelOuter[2] = gl_TessLevelOuter[0];
    gl_TessLevelOuter[3] = gl_TessLevelOuter[0];
    
    gl_TessLevelInner[0] = gl_TessLevelOuter[0];
    gl_TessLevelInner[1] = gl_TessLevelOuter[0];
    bPosition = Position[0];
    bRadius   = Radius[0];
}