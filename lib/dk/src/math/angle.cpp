#include <dklib/math/angle.hpp>

namespace dk::math {
std::ostream &operator<<(std::ostream &os, const Angle &angle) {
    return os << angle.radians_;
}

Angle operator""_deg(const char *value) {
    return Angle::from<Degrees>(std::stod(value));
}
Angle operator""_deg(unsigned long long value) {
    return Angle::from<Degrees>(static_cast<double>(value));
}
Angle operator""_deg(long double value) { return Angle::from<Degrees>(value); }

Angle operator""_rad(const char *value) {
    return Angle::from<Radians>(std::stod(value));
}
Angle operator""_rad(unsigned long long value) {
    return Angle::from<Radians>(static_cast<double>(value));
}
Angle operator""_rad(long double value) { return Angle::from<Radians>(value); }
} // namespace dk::math
