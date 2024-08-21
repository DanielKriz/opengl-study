#version 450 core
out vec4 color;

in VS_OUT {
    vec3 color;
    vec2 tex_coords;
} fs_in;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform bool is_blending_enabled;
uniform bool is_color_mode_enabled;

uniform float blend_factor;

vec4 color_factor = is_color_mode_enabled ? vec4(fs_in.color, 1.0) : vec4(1.0, 1.0, 1.0, 1.0);

void main()
{
    if (is_blending_enabled) {
        color = mix(
            texture(texture1, fs_in.tex_coords), 
            texture(texture2, fs_in.tex_coords),
            // This we can reverse the second image on the Y axis
            // texture2D(texture2, vec2(fs_in.tex_coords.x, 1.0 - fs_in.tex_coords.y)),
            blend_factor
        ) * color_factor;
    } else {
        color = texture(texture1, fs_in.tex_coords) * color_factor;
    }
}
