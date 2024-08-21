#ifndef DK_QUATERNION_H
#define DK_QUATERNION_H

#include <dklib/math/angle.hpp>
#include <dklib/math/vector3d.hpp>

#include <cmath>
#include <ostream>
// #include <iostream>
// #include <numbers>

namespace dk::math {

class Quaternion {
public:
    /// Imaginary part of a quaternion.
    Vector3D imag;
    /// Real part of a quaternion.
    float real;

    Quaternion() = default;

    /// Default exhaustive constructor for Quaternion class.
    ///
    /// It delegates most work to the vector based constructor.
    ///
    /// @param  [in] a,b,c An imaginary part of quaternion.
    /// @param  [in] s A real part of a vector, oftern addressed as scalar.
    Quaternion(float a, float b, float c, float s);
    Quaternion(float a, float b, float c, Angle angle);

    /// Constructor for so-called pure quaternion, i.e. quaternion which real part
    /// is equal to zero.
    ///
    /// It delegates most work to the vector based constructor.
    Quaternion(float a, float b, float c);
    // TODO: this migh be usable still..
    // TODO: document this
    // Quaternion(const Vector3D &vec);

    /// Constuctor which represents the imaginary part as a vector.
    Quaternion(const Vector3D &vec, float s);
    Quaternion(const Vector3D &vec, Angle s);

    /* Quaternion(const Quaternion &other)
        : Quaternion(other.imag, other.real) {}; */

    // Quaternion &operator=(const Quaternion &other) = default;

    /* Quaternion(Quaternion &&other) noexcept
        : imag(other.imag)
        , real(other.real) {};

    Quaternion &operator=(Quaternion &&other) noexcept {
        std::swap(imag, other.imag);
        std::swap(real, other.real);
        return *this;
    } */

    /// @brief Checks whether the Quaternion instance is unit quaternion.
    ///
    /// Unit quaternion is a quaternion which magnitude is equal to one.
    ///
    /// @return True if the quaternion is indeed unit quaternion.
    [[nodiscard]] bool is_unit() const;

    /// @brief Checks whether the quaternion is pure.
    ///
    /// Quaternion is pure when its real part is equal to zero.
    ///
    /// @return True if the quaternion is indeed pure.
    [[nodiscard]] bool is_pure() const noexcept;

    /// @brief Accessor to the imaginary part.
    ///
    /// @return Vector representing the copy of imaginary part of our quaternion.
    [[nodiscard]] Vector3D vector_part() const;

    /// Equality operators.
    friend bool operator==(const Quaternion &lhs, const Quaternion &rhs);
    friend bool operator!=(const Quaternion &lhs, const Quaternion &rhs);

    /// Equality operators.
    Quaternion &operator*=(const Quaternion &other) noexcept;
    Quaternion &operator-=(const Quaternion &other) noexcept;
    Quaternion &operator+=(const Quaternion &other) noexcept;

    friend Quaternion operator*(const Quaternion &lhs, const Quaternion &rhs);
    friend Quaternion operator+(const Quaternion &lhs, const Quaternion &rhs);
    friend Quaternion operator-(const Quaternion &lhs, const Quaternion &rhs);

    friend std::ostream &operator<<(std::ostream &os, const Quaternion &quat);

    /// @brief rotates given vector around given axis with given angle.
    ///
    /// @param  [in] vec A vector which we want to rotate.
    /// @param  [in] angle An angle in degrees.
    /// @param  [in] axis Axis over which we are going to rotate our vector,
    ///                   it can be any arbitrary axis.
    ///
    /// @return Rotated copy (which is created as copy of the original vector).
    static Vector3D rotate(const Vector3D &vec, Angle angle, const Vector3D &axis);

    /// @brief Returns the norm of quaternion.
    ///
    /// In the case of quaternions, the norm is equal to the square root of sum
    /// of the dot product of imaginary part and squared value of real part.
    ///
    /// @return Value of the normalization factor of current Quaternion instance.
    [[nodiscard]] float norm() const noexcept;

    /// @brief Returns the squared norm of quaternion.
    ///
    /// As the `sqrt` is notoriously slow, when we would need the squared norm
    /// value, it much more efficient to simply don't apply the square root at
    /// the first place.
    ///
    /// @return Squared value of the normalization factor of current Quaternion
    /// instance.
    [[nodiscard]] float norm_squared() const noexcept;

    /// @brief Returns normalized unit quaternion with respect to the angle.
    ///
    /// As a side effect this function transform the real part to radians.
    [[nodiscard]] Quaternion unit_norm() const noexcept;

    /// @brief Mutating variant of `unit_norm` method.
    Quaternion &to_unit_norm() noexcept;

    /// @brief Returns pure equivalent of our Quaternion instance.
    [[nodiscard]] Quaternion pure() const noexcept;

    /// @brief Mutating variant of `pure` method.
    Quaternion &to_pure() noexcept;

    /// @brief Returns normalized quaternion.
    [[nodiscard]] Quaternion normalized() const;

    /// @brief Mutating variant of normalized quaternion.
    Quaternion &normalize();

    /// @brief Returns the conjugate of our Quaternion instance.
    ///
    /// The conjugate quaternion has its imaginary part negated.
    [[nodiscard]] Quaternion conjugate() const noexcept;

    /// @brief Returns the inverse of our Quaternion instance.
    [[nodiscard]] Quaternion inverse() const noexcept;
};

static_assert(std::is_trivial_v<Quaternion>);
static_assert(std::is_standard_layout_v<Quaternion>);

} // namespace dk::math

#endif // DK_QUATERNION_H
