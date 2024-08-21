/// @file vector3d.hpp
/// @brief Interface of a class representing 3D vector.
/// @author Daniel Kříž
#ifndef DK_MATH_VECTOR_3D_HPP
#define DK_MATH_VECTOR_3D_HPP

#include <algorithm>
#include <cmath>
#include <concepts>
#include <ostream>
#include <stdexcept>
#include <utility>

#include <dklib/math/vector.hpp>

namespace dk::math {

// template <typename T, std::size_t Dims>
// class Vector { };

/// @brief Class representing a 3D vector.
///
/// Class representing a 3D vector, with many mathematical operations. It has
/// public default visibility as it makes the client code more readable and
/// this is a simple class that does not require too much encapsulation.
///
/// It is aligned to 16 bytes to make it fit into the memory and make it easier
/// to use in OpenGL uniforms.
///
/// It is not possible to inherit this class as it was not designed for this
/// purpose.
class Vector3D {
public:
  using point_type = std::pair<int, int>;

  /// @brief Default constructor that assigns a 0 to each vector member.
  // constexpr Vector3D()
  //     : elems_ { 0.0f }
  //     , x(elems_[0])
  //     , y(elems_[1])
  //     , z(elems_[2]) {};
  constexpr Vector3D() = default;
  // constexpr Vector3D()
  //     : x(0.0f)
  //     , y(0.0f)
  //     , z(0.0f) {};

  /// @brief Constructor with single value that initializes each member to
  /// provided value.
  ///
  /// This constructor is explicitly marked as implicit as we want other
  /// types to be able to be used with it.
  explicit(false) constexpr Vector3D(float value)
      : x(value), y(value), z(value){};

  /// @brief Constructor with multiple value that initializes each member to
  /// provided value for every single one.
  constexpr Vector3D(float x_value, float y_value, float z_value)
      // : elems_ { x_value, y_value, z_value }
      : x(x_value), y(y_value), z(z_value){};

  // ~Vector3D() = default;

  /* Vector3D(const Vector3D &other)
      : Vector3D(other.x, other.y, other.z) {}; */

  /* Vector3D &operator=(const Vector3D &other) {
      x = other.x;
      y = other.y;
      z = other.z;
      return *this;
  } */

  /* Vector3D(Vector3D &&other) noexcept
      : Vector3D(other.x, other.y, other.z) {}; */

  /* Vector3D &operator=(Vector3D &&other) noexcept {
      std::swap(x, other.x);
      std::swap(y, other.y);
      std::swap(z, other.z);
      return *this;
  } */

  /// @brief Factory method for unit vector, that is, vector containing only
  /// ones.
  inline static constexpr Vector3D unit() noexcept { return {1.0f}; };
  /// @brief Factory method for unit vector, that is, vector containing only
  /// zeroes.
  inline static constexpr Vector3D zero() noexcept { return {0.0f}; };

  inline static constexpr Vector3D x_axis() noexcept {
    return {1.0f, 0.0f, 0.0f};
  }

  inline static constexpr Vector3D y_axis() noexcept {
    return {0.0f, 1.0f, 0.0f};
  }

  inline static constexpr Vector3D z_axis() noexcept {
    return {0.0f, 0.0f, 1.0f};
  }

  inline static constexpr Vector3D x_axis(const Vector3D &vec) noexcept {
    return {vec.x, 0.0f, 0.0f};
  }

  inline static constexpr Vector3D y_axis(const Vector3D &vec) noexcept {
    return {0.0f, vec.y, 0.0f};
  }

  inline static constexpr Vector3D z_axis(const Vector3D &vec) noexcept {
    return {0.0f, 0.0f, vec.z};
  }

  // /// @brief Creates a vector with the value of the x axis of this vector
  // /// instance. Other values are set to zero.
  // [[nodiscard]] constexpr Vector3D x_axis() const noexcept {
  //     return { x, 0.0f, 0.0f };
  // }
  //
  // /// @brief Creates a vector with the value of the y axis of this vector
  // /// instance. Other values are set to zero.
  // [[nodiscard]] constexpr Vector3D y_axis() const noexcept {
  //     return { 0.0f, y, 0.0f };
  // }
  //
  // /// @brief Creates a vector with the value of the z axis of this vector
  // /// instance. Other values are set to zero.
  // [[nodiscard]] constexpr Vector3D z_axis() const noexcept {
  //     return { 0.0f, 0.0f, z };
  // }
  friend constexpr auto operator+(const Vector3D &lhs,
                                  const Vector3D &rhs) noexcept;
  friend constexpr auto operator-(const Vector3D &lhs,
                                  const Vector3D &rhs) noexcept;
  friend constexpr auto operator*(const Vector3D &lhs,
                                  const Vector3D &rhs) noexcept;
  friend constexpr auto operator/(const Vector3D &lhs, const Vector3D &rhs);
  friend constexpr auto operator*(const Vector3D &vec, float value) noexcept;
  friend constexpr auto operator/(const Vector3D &vec, float value);

  /// @brief Negation operator.
  /// @return Reference to this vector with all of its elements negated.
  constexpr auto operator-() const noexcept { return Vector3D(-x, -y, -z); };

  /// @brief Addition with self-assignment.
  ///
  /// @param  [in] other Vector whose elements we are adding to this instance
  ///              of 3D vector.
  /// @return Reference to this vector which now has all of its elements
  ///         added to the values of the other vector.
  constexpr auto &operator+=(const Vector3D &other) noexcept {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  };

  /// @brief Subtraction with self-assignment.
  ///
  /// @param  [in] other Vector whose elements we are subtracting with this
  ///              instance of 3D vector.
  /// @return Reference to this vector which now has all of its elements
  ///         subtracted by the values of the other vector.
  constexpr auto &operator-=(const Vector3D &other) noexcept {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  };

  /// @brief Multiplication with 3D vector with self-assignment.
  ///
  /// @param  [in] other Vector with whose elements we are multiplying with
  ///              elements of this 3D vector instance.
  /// @return Reference to this vector which now has all of its elements
  ///         multiplied by the values of the other vector.
  constexpr auto &operator*=(const Vector3D &other) noexcept {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
  };

  /// @brief Division with 3D vector with self-assignment.
  ///
  /// @throws std::runtime_error When any element of provided divisor vector is
  ///                            equal to 0.
  ///
  /// @param  [in] other Vector with whose elements we are dividing with
  ///              elements of this 3D vector instance.
  /// @return Reference to this vector which now has all of its elements
  ///         divided by the elements of provided vector.
  constexpr auto &operator/=(const Vector3D &other) {
    if (other.x == 0.0f or other.y == 0.0f or other.z == 0.0f) {
      throw std::runtime_error("Division by zero");
    }
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
  };

  /// @brief Multiplication with self-assignment.
  /// @param  [in] value Scalar which is going to multiply each member of
  ///              this 3D vector instance.
  /// @return Reference to this vector which now has all of its elements
  ///         multiplied by the provided value.
  constexpr auto &operator*=(float value) noexcept {
    x *= value;
    y *= value;
    z *= value;
    return *this;
  };

  /// @brief Division with self-assignment.
  ///
  /// @throws std::runtime_error When the scalar value is equal to 0.
  ///
  /// @param  [in] value Scalar which is going to divide each member of
  ///              this 3D vector instance.
  /// @return Reference to this vector which now has all of its elements
  ///         divided by the provided value.
  constexpr auto &operator/=(float value) {
    if (value == 0.0f) {
      throw std::runtime_error("Division by zero");
    }
    x /= value;
    y /= value;
    z /= value;
    return *this;
  };

  /// @brief Equivalence operator.
  friend constexpr bool operator==(const Vector3D &lhs,
                                   const Vector3D &rhs) noexcept;

  // TODO: check std::lexicographical_compare_three_way
  friend constexpr auto operator<=>(const Vector3D &lhs,
                                    const Vector3D &rhs) noexcept;

  /// @brief Computes magnitude, i.e. size of this vector instance.
  ///
  /// The function can be marked as `noexpect` as it is not possible to pass
  /// a negative number to the squre root function, because all of the values
  /// are squared.
  ///
  /// @return Magnitude of this vector instance.
  [[nodiscard]] constexpr float magnitude() const noexcept {
    return std::sqrt(this->dot(*this));
  };
  friend constexpr float magnitude(const Vector3D &vec) noexcept;

  /// @brief Computes squared magnitude of ths vector instance.
  ///
  /// The function can be marked as `noexpect` as it is not possible to pass
  /// a negative number to the squre root function, because all of the values
  /// are squared.
  ///
  /// @return Squared magnitude of this vector instance.
  [[nodiscard]] constexpr float magnitude_squared() const noexcept {
    return this->dot(*this);
  };
  friend constexpr float magnitude_squared(const Vector3D &vec) noexcept;

  /// @brief Method for computation of the dot product.
  ///
  /// @param  [in] other The vector to which we are projecting.
  ///
  /// @return The value of dot product between this vector instance and
  ///         provided vector.
  [[nodiscard]] float dot(const Vector3D &other) const noexcept;
  friend constexpr float dot(const Vector3D &lhs, const Vector3D &rhs) noexcept;

  /// @brief Method for computation of cross product.
  [[nodiscard]] Vector3D cross(const Vector3D &other) const;
  friend constexpr Vector3D cross(const Vector3D &lhs, const Vector3D &rhs);

  /// @brief Computes the sum of all elements in this vector instance.
  /// @return The sum of all dimensions of a vector.
  [[nodiscard]] float sum() const noexcept;

  /// @brief Computes the sum of this vector instance and provided vector.
  ///
  /// @param  [in] other Vector which we are going to add to the sum of our
  ///              3D vector instance.
  ///
  /// @return Sum of all dimensions of this vector instance and
  /// all dimensions of provided vector.
  [[nodiscard]] float sum(const Vector3D &other) const noexcept;
  friend constexpr float sum(const Vector3D &lhs, const Vector3D &rhs) noexcept;

  /// @brief Clamps copy of this vector instance between min and max.
  ///
  /// @param  [in] min Lower bound for clamping
  /// @param  [in] max Upper bound for clamping.
  ///
  /// @return Clamped version of this vector instance between min and max.
  [[nodiscard]] Vector3D clamped(float min, float max) const;

  /// @brief Clamps vector between min and max.
  ///
  /// @param  [in] min Lower bound for clamping
  /// @param  [in] max Upper bound for clamping.
  ///
  /// @return Reference to this vector instance, which is now clamped between
  ///         min and max.
  Vector3D &clamp(float min, float max);
  friend constexpr Vector3D clamp(const Vector3D &vec, float min, float max);

  // Since std::ceil, std::floor, std::Abs and std::round are not marked as
  // noexpect, because error handling is implementation dependent, we cannot
  // mark these functions as noexpect.

  friend constexpr Vector3D abs(const Vector3D &vec);
  /// @brief Creates an absolute copy of a vector instance.
  ///
  /// @return Absolute value copy of a vector instance.
  [[nodiscard]] Vector3D absed() const;

  /// @brief Makes all elements of this vector instance absolute.
  ///
  /// @return Reference to a vector instance with elements in absolute value.
  Vector3D &abs();

  friend constexpr Vector3D ceil(const Vector3D &vec);
  /// @brief Creates a ceiled copy of a vector instance.
  ///
  /// @return Ceiled copy of a vector instance.
  [[nodiscard]] Vector3D ceiled() const;

  /// @brief Ceils a vector instance.
  ///
  /// @return Reference to a now ceiled vector instance.
  Vector3D &ceil();

  friend constexpr Vector3D floor(const Vector3D &vec);
  /// @brief Creates a floored copy of a vector instance.
  ///
  /// @return Floored copy of a vector instance.
  [[nodiscard]] Vector3D floored() const;

  /// @brief Creates a floored copy of a vector instance.
  ///
  /// @return Reference to a floored vector instance.
  Vector3D &floor();

  friend constexpr Vector3D round(const Vector3D &vec);
  /// @brief Creates rounded copy of a vector instance.
  ///
  /// @return Rounded copy of a vector instance.
  [[nodiscard]] Vector3D rounded() const;

  /// @brief Rounds a vector instance.
  ///
  /// @return Reference to rounded vector instance.
  Vector3D &round();

  friend constexpr float norm(const Vector3D &vec);

  /// @brief Computes a norm of a vector instance.
  ///
  /// Norm is basically vector's magnitude.
  ///
  /// @return Norm of a vector instance.
  [[nodiscard]] float norm() const;

  friend constexpr Vector3D normalize(const Vector3D &vec);
  [[nodiscard]] Vector3D normalized() const;
  Vector3D &normalize();

  [[nodiscard]] bool is_perpendicular(const Vector3D &other) const noexcept {
    return this->dot(other) == 0.0f;
  };
  friend bool is_perpendicular(const Vector3D &other) noexcept;

  [[nodiscard]] bool is_parallel(const Vector3D &other) const noexcept {
    return this->cross(other).magnitude_squared() == 0.0f;
  };
  friend bool is_parallel(const Vector3D &other) noexcept;

  // TODO: Implement when the angle class is ready
  // friend constexpr float angle(const Vector3D &lhs, const Vector3D &rhs);
  // constexpr float angle(const Vector3D &other);

  /// @brief Compatibility operator with streams.
  ///
  /// @param  [in] os Outcoming output stream.
  /// @param  [in] vec Vector which we want to represent as a string.
  friend std::ostream &operator<<(std::ostream &os, const Vector3D &vec);

  constexpr float get_x() noexcept;
  constexpr float get_y() noexcept;
  constexpr float get_z() noexcept;

private:
  /// We need the values to be stored in continous memory, because we need to
  /// pass them to e.g. opengl uniforms as an uniform view to memory.
  // std::array<float, 3> elems_;

public:
  // These references are making this vector much bigger, as we have to
  // store them, but it makes the ergonomics of this class much better.

  /// @brief Element of vector representing the X axis.
  /// It has public visibility.
  float x;
  /// @brief Element of vector representing the y axis.
  /// It has public visibility.
  float y;
  /// @brief Element of vector representing the z axis.
  /// It has public visibility.
  float z;
};

// TODO: This should probably also apply
static_assert(std::is_trivial_v<Vector3D>);
static_assert(std::is_standard_layout_v<Vector3D>);

/// @brief Addition symetric operator between two 3D vectors
///
/// @param  [in] lhs First of the two vectors.
/// @param  [in] rhs Second of the two vectors.
///
/// @return New 3D vector instance which contains result of addition of
/// two provided vectors.
constexpr auto operator+(const Vector3D &lhs, const Vector3D &rhs) noexcept {
  return Vector3D{lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

/// @brief Subtraction symetric operator between two 3D vectors
///
/// @param  [in] lhs First of the two vectors.
/// @param  [in] rhs Second of the two vectors.
///
/// @returns New 3D vector instance which contains result of subtraction of
/// two provided vectors.
constexpr auto operator-(const Vector3D &lhs, const Vector3D &rhs) noexcept {
  return Vector3D{lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

/// @brief Multiplication symetric operator between two 3D vectors
///
/// @param  [in] lhs First of the two vectors.
/// @param  [in] rhs Second of the two vectors.
///
/// @return New 3D vector instance which contains result of multiplication of
/// two provided vectors.
constexpr auto operator*(const Vector3D &lhs, const Vector3D &rhs) noexcept {
  return Vector3D{lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
}

/// @brief Division symetric operator between two 3D vectors
///
/// @throws std::runtime_error When any element of divisor (right) vector is
///                            equal to 0.
///
/// @param  [in] lhs First of the two vectors.
/// @param  [in] rhs Second of the two vectors.
///
/// @return New 3D vector instance which contains result of division of
/// two provided vectors.
constexpr auto operator/(const Vector3D &lhs, const Vector3D &rhs) {
  if (rhs.x == 0.0f or rhs.y == 0.0f or rhs.z == 0.0f) {
    throw std::runtime_error("Division by zero");
  }
  return Vector3D{lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z};
}

/// @brief Multiplication symetric operator between two 3D vectors
///
/// @param  [in] vec Vector whose elements we are going to multiply.
/// @param  [in] value Scalar value which represents the resulting multiple.
///
/// @return New 3D vector instance which contains result of multiplication of
/// vector and scalar. This operator is symmetric.
constexpr auto operator*(const Vector3D &vec, const float value) noexcept {
  return Vector3D{vec.x * value, vec.y * value, vec.z * value};
}

/// @brief Division symetric operator between two 3D vectors
///
/// @throws std::runtime_error When scalar value is equal to 0.
///
/// @param  [in] vec Vector whose elements we are going to divide.
/// @param  [in] value Scalar value which represents divisor.
///
/// @return New 3D vector instance which contains result of division of
/// vector and scalar. This operator is symmetric.
constexpr auto operator/(const Vector3D &vec, const float value) {
  if (value == 0.0f) {
    throw std::runtime_error("Division by zero");
  }
  return Vector3D{vec.x / value, vec.y / value, vec.z / value};
}

/// @brief Check whether the two provided vectors are equal.
///
/// @param  [in] lhs First of the two vectors.
/// @param  [in] rhs Second of the two vectors.
///
/// @return True if elemens of two vectors are equivalent.
constexpr bool operator==(const Vector3D &lhs, const Vector3D &rhs) noexcept {
  return ((lhs.x == rhs.x) and (lhs.y == rhs.y) and (lhs.z == rhs.z));
}

// TODO: this one is missing:
// [ ] Documentation
// [ ] Unit tests
constexpr auto operator<=>(const Vector3D &lhs, const Vector3D &rhs) noexcept {
  return lhs.magnitude() <=> rhs.magnitude();
}

/// @brief Computes a magnitude, i.e. size of a provided vector.
///
/// The function can be marked as `noexpect` as it is not possible to pass
/// a negative number to the squre root function, because all of the values
/// are squared.
///
/// @param  [in] vec Vector for which we are computing the magnitude.
///
/// @return Magnitude of provided vector.
constexpr float magnitude(const Vector3D &vec) noexcept {
  return vec.magnitude();
}

/// @brief Computes squared magnitude of a provided vector
///
/// Many times the magnitude is required to be squared, thus with call of this
/// function we can omit the call of expensive square root function.
/// The function can be marked as `noexpect` as we are not calling the square
/// root function.
///
/// @param  [in] vec Vector for which we are computing the squared magnitude.
///
/// @return Squared magnitude of a provided vector.
constexpr float magnitude_squared(const Vector3D &vec) noexcept {
  return vec.magnitude_squared();
}

/// @brief Computes dot product of two vectors.
///
/// @param  [in] lhs First of the two vectors.
/// @param  [in] lhs Second of the two vectors.
///
/// @return Dot product of two provided vectors.
constexpr float dot(const Vector3D &lhs, const Vector3D &rhs) noexcept {
  return lhs.dot(rhs);
}

/// @brief Computes Cross product of two vectors.
///
/// @param  [in] lhs First of the two vectors.
/// @param  [in] lhs Second of the two vectors.
///
/// @return Cross product of two provided vectors.
constexpr Vector3D cross(const Vector3D &lhs, const Vector3D &rhs) {
  return lhs.cross(rhs);
}

/// @brief Sum of two vectors.
///
/// @param  [in] lhs First of the two vectors.
/// @param  [in] lhs Second of the two vectors.
constexpr float sum(const Vector3D &lhs, const Vector3D &rhs) noexcept {
  return lhs.sum() + rhs.sum();
}

/// @brief Clamps copy of provided vector between min and max.
///
/// @param  [in] vec Vector whose copy is going to be clamped.
/// @param  [in] min Lower bound for clamping
/// @param  [in] max Upper bound for clamping.
///
/// @return Clamped version of the provided vector between min and max.
constexpr Vector3D clamp(const Vector3D &vec, float min, float max) {
  return vec.clamped(min, max);
}

/// @brief Creates absolute version of provided vector.
///
/// @param  [in] vec Original vector.
///
/// @return New instance containing absolute values of provided vector.
constexpr Vector3D abs(const Vector3D &vec) { return vec.absed(); }

/// @brief Creates ceiled version of provided vector.
///
/// It does not change the original vector.
///
/// @param  [in] vec Vector that is going to be ceiled.
///
/// @return New instance containing ceiled values of provided vector.
constexpr Vector3D ceil(const Vector3D &vec) { return vec.ceiled(); }

/// @brief Creates floored version of provided vector.
///
/// It does not change the original vector.
///
/// @param  [in] vec Vector that is going to be floored.
///
/// @return New instance containing floored values of provided vector.
constexpr Vector3D floor(const Vector3D &vec) { return vec.floored(); }

/// @brief Creates rounded version of provided vector.
///
/// @param  [in] vec Vector that is going to be rounded.
///
/// @return New instance containing rounded values of provided vector.
constexpr Vector3D round(const Vector3D &vec) { return vec.rounded(); }

/// @brief Computes norm of a vector.
///
/// Norm of a vector is equal to its magnitude.
///
/// @param  [in] vec Vector for which we are computing its norm.
///
/// @return Norm of a provided vector.
constexpr float norm(const Vector3D &vec) { return vec.magnitude(); }

constexpr Vector3D normalize(const Vector3D &vec) {
  // TODO: this is missing unit tests
  return vec / magnitude(vec);
}

// TODO: I have an angle class, so this is doable
// constexpr float angle(const Vector3D &lhs, const Vector3D &rhs) { return
// 0.0f; }

} // namespace dk::math
#endif // DK_MATH_VECTOR_3D_HPP
