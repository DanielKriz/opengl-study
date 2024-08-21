#ifndef DK_MATH_ANGLE_HPP
#define DK_MATH_ANGLE_HPP

// TODO: document this class

#include <cmath>
#include <compare>
#include <numbers>
#include <ostream>

#include <dklib/math/math_concepts.hpp>

namespace dk::math {

class Angle {
public:
    // TODO: this looks more like a RadianConvertible
    template <AngleConvertible Representation>
    static inline constexpr Angle from(double value) {
        return Angle { Representation::to_radians(value) };
    }

    template <AngleConvertible Representation>
    [[nodiscard]] static inline constexpr double as(double value) {
        return Representation::from_radians(value);
    }

    auto operator<=>(const Angle &other) const = default;

    operator double() const { return radians_; }

    constexpr explicit Angle(double radians)
        : radians_ { radians } {};

    friend std::ostream &operator<<(std::ostream &os, const Angle &angle);

protected:
    /// Default internal representation is in radians, this makes it possible
    /// to suffice the open-closed principle.
    double radians_;
};

// TODO: add osstream friend operator for repr
// TODO: check what is going to happen for Degrees + Radians
// FIXME: Should these hold a value, or is it just different interpretation of
// a floating point value.

class Degrees : public Angle {
public:
    static inline constexpr double to_radians(double degrees) {
        return degrees * radian_coversion_coef;
    }

    static inline constexpr double from_radians(double radians) {
        return radians / radian_coversion_coef;
    }
    // [[nodiscard]] Degrees normalize(double min, double max) const noexcept;

    // [[nodiscard]] bool is_valid() const noexcept;
    // inline static bool is_valid(Degrees deg) noexcept;

private:
    static constexpr double radian_coversion_coef = std::numbers::pi / 180.0;
};

Angle operator""_deg(const char *value);
Angle operator""_deg(unsigned long long value);
Angle operator""_deg(long double value);

// we want to be sure than we don't have to create reference
static_assert(sizeof(Degrees) == sizeof(double));
static_assert(std::is_trivially_copyable<Degrees>());

class Radians : public Angle {
public:
    static inline double constexpr to_radians(double radians) { return radians; }
    // [[nodiscard]] Radians normalize(double min, double max) const noexcept;

private:
};

Angle operator""_rad(const char *value);
Angle operator""_rad(unsigned long long value);
Angle operator""_rad(long double value);

static_assert(sizeof(Radians) == sizeof(double));
static_assert(std::is_trivially_copyable<Radians>());
} // namespace dk::math

#endif // DK_MATH_ANGLE_HPP
