// Generated code, do not modify this file!
// Generated on 2023-04-04T01:24:40.539Z by mwilsnd using shaders/generate_shader_code.js

#pragma once
#include <mbgl/shaders/shader_source.hpp>

namespace mbgl {
namespace shaders {

template <>
struct ShaderSource<BuiltIn::BackgroundPatternProgram, gfx::Backend::Type::OpenGL> {
    static constexpr const char* vertex = R"(uniform mat4 u_matrix;
uniform vec2 u_pattern_size_a;
uniform vec2 u_pattern_size_b;
uniform vec2 u_pixel_coord_upper;
uniform vec2 u_pixel_coord_lower;
uniform float u_scale_a;
uniform float u_scale_b;
uniform float u_tile_units_to_pixels;

attribute vec2 a_pos;

varying vec2 v_pos_a;
varying vec2 v_pos_b;

void main() {
    gl_Position = u_matrix * vec4(a_pos, 0, 1);

    v_pos_a = get_pattern_pos(u_pixel_coord_upper, u_pixel_coord_lower, u_scale_a * u_pattern_size_a, u_tile_units_to_pixels, a_pos);
    v_pos_b = get_pattern_pos(u_pixel_coord_upper, u_pixel_coord_lower, u_scale_b * u_pattern_size_b, u_tile_units_to_pixels, a_pos);
}
)";
    static constexpr const char* fragment = R"(uniform vec2 u_pattern_tl_a;
uniform vec2 u_pattern_br_a;
uniform vec2 u_pattern_tl_b;
uniform vec2 u_pattern_br_b;
uniform vec2 u_texsize;
uniform float u_mix;
uniform float u_opacity;

uniform sampler2D u_image;

varying vec2 v_pos_a;
varying vec2 v_pos_b;

void main() {
    vec2 imagecoord = mod(v_pos_a, 1.0);
    vec2 pos = mix(u_pattern_tl_a / u_texsize, u_pattern_br_a / u_texsize, imagecoord);
    vec4 color1 = texture2D(u_image, pos);

    vec2 imagecoord_b = mod(v_pos_b, 1.0);
    vec2 pos2 = mix(u_pattern_tl_b / u_texsize, u_pattern_br_b / u_texsize, imagecoord_b);
    vec4 color2 = texture2D(u_image, pos2);

    gl_FragColor = mix(color1, color2, u_mix) * u_opacity;

#ifdef OVERDRAW_INSPECTOR
    gl_FragColor = vec4(1.0);
#endif
}
)";
};

} // namespace shaders
} // namespace mbgl
