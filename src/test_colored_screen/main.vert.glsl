#version 450 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_color;

out VS_OUT {
    vec3 color;
};

void main(void) {
    gl_Position = vec4(in_position, 1.0);
    color = in_color;
}
