#include <dklib/math/vector3d.hpp>

namespace dk::math {

// TODO: check std::lexicographical_compare_three_way
float Vector3D::dot(const Vector3D &other) const noexcept {
    return (x * other.x + y * other.y + z * other.z);
}

Vector3D Vector3D::cross(const Vector3D &other) const {
    Vector3D res = { this->y * other.z - this->z * other.y,
                     this->z * other.x - this->x * other.z,
                     this->x * other.y - this->y * other.x };
    // We are doing this to avoid having negative zero in the result.
    return res + Vector3D(0.0f, 0.0f, 0.0f);
}

float Vector3D::sum() const noexcept { return (x + y + z); }
float Vector3D::sum(const Vector3D &other) const noexcept {
    return sum() + other.sum();
}

Vector3D Vector3D::clamped(float min, float max) const {
    auto copy = *this;
    copy.clamp(min, max);
    return copy;
}

Vector3D &Vector3D::clamp(float min, float max) {
    x = std::clamp(x, min, max);
    y = std::clamp(y, min, max);
    z = std::clamp(z, min, max);
    return *this;
}

Vector3D Vector3D::absed() const {
    auto copy = *this;
    copy.abs();
    return copy;
}

Vector3D &Vector3D::abs() {
    x = std::abs(x);
    y = std::abs(y);
    z = std::abs(z);
    return *this;
}

Vector3D Vector3D::ceiled() const {
    auto copy = *this;
    copy.ceil();
    return copy;
}

Vector3D &Vector3D::ceil() {
    x = std::ceil(x);
    y = std::ceil(y);
    z = std::ceil(z);
    return *this;
}

Vector3D Vector3D::floored() const {
    auto copy = *this;
    copy.floor();
    return copy;
}

Vector3D &Vector3D::floor() {
    x = std::floor(x);
    y = std::floor(y);
    z = std::floor(z);
    return *this;
}

Vector3D Vector3D::rounded() const {
    auto copy = *this;
    copy.round();
    return copy;
}

Vector3D &Vector3D::round() {
    x = std::round(x);
    y = std::round(y);
    z = std::round(z);
    return *this;
}

float Vector3D::norm() const { return magnitude(); }

Vector3D Vector3D::normalized() const {
    auto copy = *this;
    copy.normalize();
    return copy;
}
Vector3D &Vector3D::normalize() {
    *this /= this->magnitude();
    return *this;
}

// TODO: Implement when the angle class is ready
// constexpr float angle(const Vector3D &other) { return 0.0f; }

std::ostream &operator<<(std::ostream &os, const Vector3D &vec) {
    return os << '(' << vec.x << ", " << vec.y << ", " << vec.z << ')';
}
} // namespace dk::math
