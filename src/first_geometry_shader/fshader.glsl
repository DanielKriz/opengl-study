#version 450 core

// input from vertex shader
// in vec4 vs_color;
in VS_OUT {
    vec4 color;
} fs_in;

// output to the framebuffer
out vec4 color;

void main(void) {
    color = vec4(0.0, 0.8, 1.0, 1.0);
}
