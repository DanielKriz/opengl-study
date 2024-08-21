#include <dklib/math/quaternion.hpp>

namespace dk::math {

Quaternion::Quaternion(float a, float b, float c, float scalar)
    : imag(a, b, c)
    , real(scalar) { }

Quaternion::Quaternion(float a, float b, float c, Angle angle)
    : imag(a, b, c)
    , real(static_cast<float>(Degrees::from_radians(angle))) {};

Quaternion::Quaternion(const Vector3D &vec, float scalar)
    : imag(vec)
    , real(scalar) { }

Quaternion::Quaternion(const Vector3D &vec, Angle angle)
    : imag(vec)
    , real(static_cast<float>(Degrees::from_radians(angle))) {};

Vector3D Quaternion::vector_part() const { return imag; }

Vector3D Quaternion::rotate(const Vector3D &vec, Angle angle, const Vector3D &axis) {
    const Quaternion pure_quat = { vec, 0.0f };
    const Vector3D rotation_axis = axis.normalized();
    const Quaternion rotation_quat = Quaternion(rotation_axis, angle).to_unit_norm();
    const Quaternion rotation_quat_inverse = rotation_quat.inverse();
    const Quaternion rotated = rotation_quat * pure_quat * rotation_quat_inverse;

    return rotated.imag;
}

bool operator==(const Quaternion &lhs, const Quaternion &rhs) {
    return (lhs.imag == rhs.imag and lhs.real == rhs.real);
}
bool operator!=(const Quaternion &lhs, const Quaternion &rhs) {
    return not(lhs == rhs);
}

std::ostream &operator<<(std::ostream &os, const Quaternion &quat) {
    return os << '(' << quat.imag.x << ", " << quat.imag.y << ", " << quat.imag.z
              << ", " << quat.real << ')';
}

bool Quaternion::is_unit() const { return *this == normalized(); }

Quaternion &Quaternion::normalize() {
    auto norm_value = norm();
    if (norm_value != 0.0f) {
        float normalization_factor = 1 / norm_value;
        imag *= normalization_factor;
        real *= normalization_factor;
    } else {
        throw std::runtime_error("Cannot normalize zero quaternion");
    }
    return *this;
}

Quaternion Quaternion::normalized() const {
    Quaternion copy = *this;
    copy.normalize();
    return copy;
}

float Quaternion::norm() const noexcept {
    return std::sqrt(dot(imag, imag) + (real * real));
}

float Quaternion::norm_squared() const noexcept {
    return (dot(imag, imag) + (real * real));
}

Quaternion Quaternion::conjugate() const noexcept { return { -imag, real }; }

bool Quaternion::is_pure() const noexcept { return real == 0.0f; }

Quaternion Quaternion::inverse() const noexcept {
    auto conj = conjugate();
    return conj * (*this * conj);
}

Quaternion &Quaternion::operator+=(const Quaternion &other) noexcept {
    imag += other.imag;
    real += other.real;
    return *this;
}

Quaternion &Quaternion::operator-=(const Quaternion &other) noexcept {
    imag -= other.imag;
    real -= other.real;
    return *this;
}

Quaternion &Quaternion::operator*=(const Quaternion &other) noexcept {
    const float new_real = real * other.real - dot(imag, other.imag);
    const Vector3D new_imag = imag * other.real + real * other.imag + cross(imag, other.imag);
    real = new_real;
    imag = new_imag;
    return *this;
}

Quaternion operator*(const Quaternion &lhs, const Quaternion &rhs) {
    auto copy = lhs;
    copy *= rhs;
    return copy;
}

Quaternion operator+(const Quaternion &lhs, const Quaternion &rhs) {
    return { lhs.imag + rhs.imag, lhs.real + rhs.real };
}

Quaternion operator-(const Quaternion &lhs, const Quaternion &rhs) {
    return { lhs.imag - rhs.imag, lhs.real - rhs.real };
}

Quaternion Quaternion::unit_norm() const noexcept {
    auto copy = *this;
    return copy.to_unit_norm();
};

Quaternion &Quaternion::to_unit_norm() noexcept {
    auto angle = Angle::from<Degrees>(static_cast<double>(real));
    imag.normalize();
    real = static_cast<float>(std::cos(angle * 0.5));
    imag *= static_cast<float>(std::sin(angle * 0.5));
    return *this;
};

Quaternion Quaternion::pure() const noexcept { return { imag, 0.0f }; }

Quaternion &Quaternion::to_pure() noexcept {
    real = 0.0f;
    return *this;
}

} // namespace dk::math
