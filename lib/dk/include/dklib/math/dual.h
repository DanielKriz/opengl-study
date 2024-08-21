#ifndef DK_DUAL_H
#define DK_DUAL_H

#include <concepts>
#include <ostream>
#include <sstream>
#include <utility>

namespace dk::math {

// TODO: use gltypes
using usize = unsigned long long;
using f32 = float;
using f64 = double;
using f128 = long double;

template <std::floating_point T = f64>
class dual {
public:
    constexpr dual(T real, T dual = 0);
    virtual ~dual() = default;

    T real() const;
    T dualx() const;

    T size() const;
    dual<T> conj(dual<T> &other) const noexcept;

    dual<T> operator*=(f64 scalar) const;
    dual<T> operator*=(dual<T> &other) const;
    dual<T> operator+=(dual<T> &other) const;
    dual<T> operator-=(dual<T> &other) const;
    dual<T> operator/=(dual<T> &other) const;
    dual<T> operator-() const;

private:
    using Mat4 = T[4];
    T real_;
    T dual_;
    Mat4 eps_ = { 0, 1, 0, 0 };
};

template <std::floating_point T>
constexpr dual<T> operator+(const dual<T> &lhs, const dual<T> &rhs) noexcept;

template <std::floating_point T>
constexpr dual<T> operator-(const dual<T> &lhs, const dual<T> &rhs) noexcept;

template <std::floating_point T>
constexpr dual<T> operator*(const dual<T> &lhs, const dual<T> &rhs) noexcept;

template <std::floating_point T>
constexpr dual<T> operator/(const dual<T> &lhs, const dual<T> &rhs) noexcept;

template <std::floating_point T>
constexpr bool operator==(const dual<T> &lhs, const dual<T> &rhs) noexcept;

template <std::floating_point T>
constexpr bool operator==(const T &lhs, const dual<T> &rhs) noexcept;

template <std::floating_point T>
constexpr bool operator==(const dual<T> &lhs, const T &rhs) noexcept;

template <std::floating_point T>
dual<T> proj(T number);

template <std::floating_point T, typename CharT, typename Traits>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> &os, const dual<T> &dual) {
    std::basic_ostringstream<CharT, Traits> tmp_os;
    tmp_os.flags(os.flags());
    tmp_os.imbue(os.getloc());
    tmp_os.precision(os.precision());
    tmp_os << '(' << dual.real() << ", " << dual.dualx() << ')';
    return os << tmp_os.str();
}

namespace literals {
    constexpr dual<f32> operator""_df(f128 arg);
    constexpr dual<f32> operator""_df(usize arg);
    constexpr dual<f64> operator""_d(f128 arg);
    constexpr dual<f64> operator""_d(usize arg);
    constexpr dual<f128> operator""_dl(f128 arg);
    constexpr dual<f128> operator""_dl(usize arg);
} // namespace literals

} // namespace dk::math

#endif // DK_DUAL_H
