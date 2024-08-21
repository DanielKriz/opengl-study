#version 460 core

layout(location=0) in vec3 vertexPos;
layout(location=1) in vec3 vertexColor;

// this is a bit more naive way of doing things
// out vec4 vs_color;
// this is the proper and more professional way
out VS_OUT {
    vec4 color;
} vs_out;

void main(void) {
    gl_Position.xyz = vertexPos;
    gl_Position.w = 1.0;
    vs_out.color = vertexColor;
}
