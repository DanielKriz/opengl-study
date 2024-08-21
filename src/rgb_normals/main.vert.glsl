#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out VS_OUT {
    vec4 color;
    vec4 normal;
} vs_out;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform mat4 scale_matrix;

void main(void) {
    vec4 final_pos = scale_matrix * vec4(position, 1.0f);
    gl_Position = proj_matrix * mv_matrix * final_pos;
    vs_out.color = final_pos * 2.0 + vec4(0.5, 0.5, 0.5, 0.0);
    vs_out.normal = vec4(normal, 0.0);
    // vs_out.normal = normal;
}
