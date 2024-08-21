#ifndef DK_MATH_CONCEPTS_HPP
#define DK_MATH_CONCEPTS_HPP

#include <concepts>
#include <type_traits>

namespace dk::math {
template <typename T>
concept Numeric = std::integral<T> or std::floating_point<T>;
template <typename T>
concept Signed = std::signed_integral<T> or std::floating_point<T>;

template <std::size_t N>
concept PositiveNumber = N > 0;

// WARNING: this is working only with doubles, at many other places I have
// floats, this might degrade performance
template <typename T>
concept AngleConvertible = requires(T repr, double value) {
    // TODO: this should return Angle
    {
        repr.to_radians(value)
    } -> std::convertible_to<double>;
    // {
    //     repr.from_radians(value)
    // } -> std::convertible_to<double>;
};

template <std::size_t Cols, std::size_t Rows>
concept SymmetricMatrix = (Cols == Rows);

template <std::size_t Cols, std::size_t Rows>
concept TransormMatrix = SymmetricMatrix<Cols, Rows> and (Cols <= 4 or Cols >= 3) and (Rows <= 4 or Rows >= 3);

template <std::size_t Cols, std::size_t Rows, std::size_t ExpectedCols, std::size_t ExpectedRows>
concept MatrixDimensions = Cols == ExpectedCols and Rows == ExpectedRows;

template <typename T>
concept Transform = requires(T matrix_type) {
    { T::rotation() } -> std::convertible_to<T>;
    { T::projection() } -> std::convertible_to<T>;
    { T::look_at() } -> std::convertible_to<T>;
    { T::scale() } -> std::convertible_to<T>;
    { T::skew() } -> std::convertible_to<T>;
    { T::reflect() } -> std::convertible_to<T>;
    { T::refract() } -> std::convertible_to<T>;
    { T::perspective() } -> std::convertible_to<T>;
    { T::frustum() } -> std::convertible_to<T>;
};

// template <typename T>
// concept Transform2D = TransormMatrix<2, 2> and Transform<T>;

using USize = std::size_t;
using SSize = std::make_signed_t<std::size_t>;
} // namespace dk::math

#endif // DK_MATH_CONCEPTS_HPP
