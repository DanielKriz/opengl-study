#ifndef DK_MATH_MATRIX_3D_HPP
#define DK_MATH_MATRIX_3D_HPP

#include <array>
#include <cmath>
#include <iterator>
#include <type_traits>

#include <fmt/format.h>

#include <dklib/math/matrix.hpp>
#include <dklib/math/vector3d.hpp>

// NOTE: Do not feel bad about code repetition, it is going to be shared in the
// Tensor class.

namespace dk::math {

// TODO: DO THIS FOR THE VECTOR TOO, IT CAN THEN BE USED!

class Matrix3D : public Matrix<float, 3, 3> {
public:
  static Matrix3D something() { return {}; }
  static Matrix3D rotation() { return {}; }

private:
};

static_assert(std::is_trivial_v<Matrix3D>);
static_assert(std::is_trivially_copyable_v<Matrix3D>);
static_assert(std::is_trivially_destructible_v<Matrix3D>);
static_assert(std::is_standard_layout_v<Matrix3D>);

} // namespace dk::math

#endif // DK_MATH_MATRIX_HPP
