#ifndef DK_MATH_MATRIX_3D_HPP
#define DK_MATH_MATRIX_3D_HPP

#include <array>
#include <cmath>
#include <iterator>
#include <type_traits>

#include <fmt/format.h>

#include <dklib/math/matrix.hpp>
#include <dklib/math/vector2d.hpp>

namespace dk::math {

// TODO: DO THIS FOR THE VECTOR TOO, IT CAN THEN BE USED!

class Matrix2D : public Matrix<float, 2, 2> {
public:
    Vector2D get_vector();

private:
};

static_assert(std::is_trivial_v<Matrix2D>);
static_assert(std::is_standard_layout_v<Matrix2D>);

} // namespace dk::math
#endif // DK_MATH_MATRIX_3D_HPP
