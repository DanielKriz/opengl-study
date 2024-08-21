#version 460 core

// this is a bit more naive way of doing things
// out vec4 vs_color;
// this is the proper and more professional way
out VS_OUT {
    vec4 color;
} vs_out;

void main(void) {
    const vec4 vertices[3] = vec4[3](
        vec4(0.25, -0.25, 0.5, 1.0),
        vec4(-0.25, 0.25, 0.5, 1.0),
        vec4(0.25, 0.25, 0.5, 1.0)
    );
    const vec4 colors[3] = vec4[3](
        vec4(1.0, 0.0, 0.0, 1.0),
        vec4(0.0, 1.0, 0.0, 1.0),
        vec4(0.0, 0.0, 1.0, 1.0)
    );

    gl_Position = vertices[gl_VertexID];
    vs_out.color = colors[gl_VertexID];
}
