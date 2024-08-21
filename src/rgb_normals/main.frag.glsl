#version 450 core

out vec4 color;

in VS_OUT {
    vec4 color;
    vec4 normal;
} fs_in;

void main(void) {
    vec4 normal = normalize(fs_in.normal);
    color = (normal + 1) * 0.5;
    // color = fs_in.normal * 0.5 + 0.5;
}
