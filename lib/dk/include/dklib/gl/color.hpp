#ifndef DK_GL_COLOR_HPP
#define DK_GL_COLOR_HPP

#include <dklib/concepts.h>
#include <dklib/gl/gltypes.hpp>

#include <GL/gl.h>

#include <cassert>
#include <iostream>
#include <tuple>

namespace dk::gl {

/// @brief Represents Color
class Color final {
    /// Alias for RGB representation of color
    // using RGB = std::tuple<u8, u8, u8>;
    /// Alias for RGB with alpha canal representation of color
    // using RGBa = std::tuple<u8, u8, u8, u8>;
    /// Alias for RGB+HLS representation of color
    using HLS = std::tuple<u8, u8, u8>;

private:
    struct alignas(4) RGBa {
        u8 red { 0 };
        u8 green { 0 };
        u8 blue { 0 };
        u8 alpha { 0 };
    };

public:
    Color() = default;
    explicit Color(RGBa rgba)
        : red_(rgba.red)
        , green_(rgba.green)
        , blue_(rgba.blue)
        , alpha_(rgba.alpha) {};
    // explicit Color(RGB &rgb, HLS &hls);
    explicit Color(u8 red, u8 green, u8 blue)
        : red_(red)
        , green_(green)
        , blue_(blue) {};
    explicit Color(u8 red, u8 green, u8 blue, u8 alpha)
        : red_(red)
        , green_(green)
        , blue_(blue)
        , alpha_(alpha) {};
    Color(const Color &other) = default;
    constexpr Color(Color &&other) noexcept = default;
    Color &operator=(const Color &other) = default;
    Color &operator=(Color &&other) noexcept = default;

    ~Color() = default;

    /// Setter of red component of RGB
    inline void set_red(u8 red) noexcept { red_ = red; };
    /// Setter of green component of RGB
    inline void set_green(u8 green) noexcept { green_ = green; };
    /// Setter of blue component of RGB
    inline void set_blue(u8 blue) noexcept { blue_ = blue; };
    /// Setter of aplha component of RGBa
    inline void set_alpha(u8 alpha) noexcept { alpha_ = alpha; };

    /// Setter of aplha component of RGBa
    inline void set_RGBa(RGBa &rgba) noexcept {
        red_ = rgba.red;
        green_ = rgba.green;
        blue_ = rgba.blue;
        alpha_ = rgba.alpha;
    };

    // inline void set_hue(u8 hue) noexcept;
    // inline void set_luminance(u8 luminance) noexcept;
    // inline void set_saturation(u8 saturation) noexcept;
    // inline void set_HLS(HLS rgb) noexcept;
    // inline void set_HLS(u8 hue, u8 luminance, u8 saturation) noexcept;

    [[nodiscard]] inline u8 get_red() const noexcept { return red_; };
    [[nodiscard]] inline u8 get_blue() const noexcept { return blue_; };
    [[nodiscard]] inline u8 get_green() const noexcept { return green_; };
    [[nodiscard]] inline u8 get_alpha() const noexcept { return alpha_; };

    // [[nodiscard]] inline RGB get_RGB() const noexcept;
    [[nodiscard]] inline RGBa get_RGBa() const noexcept;

private:
    u8 red_ { 0 };
    u8 green_ { 0 };
    u8 blue_ { 0 };
    u8 alpha_ { 0 };
    // u8 hue_;
    // u8 luminance_;
    // u8 saturation_;
};

static_assert(std::is_trivially_copyable_v<Color>);
static_assert(std::is_standard_layout_v<Color>);

inline std::ostream &operator<<(std::ostream &os, Color &color) {
    auto tmp_fmt_settings = os.flags();
    os << std::hex << color.get_red() << color.get_blue() << color.get_green();
    os.setf(tmp_fmt_settings);
    return os;
}

gl::f32 to_normalized_range(gl::u8 value) noexcept {
    return static_cast<gl::f32>(value) / 255.0f;
}

gl::u8 to_normalized_range(gl::f32 value) noexcept {
    return static_cast<gl::u8>(value * 255.0f);
}

template <math::Numeric T>
void set_color(const Color &color) {
    glColor4ub(color.get_red(), color.get_blue(), color.get_green(), color.get_alpha());
}

template <>
void set_color<float>(const Color &color) {
    glColor4f(to_normalized_range(color.get_red()), to_normalized_range(color.get_blue()), to_normalized_range(color.get_green()), to_normalized_range(color.get_alpha()));
}

} // namespace dk::gl

#endif // DK_GL_COLOR_HPP
