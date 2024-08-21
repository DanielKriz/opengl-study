#ifndef DK_MATH_VECTOR_HPP
#define DK_MATH_VECTOR_HPP

#include <algorithm>
#include <array>
#include <span>

#include <dklib/math/math_concepts.hpp>

namespace dk::math {

template <Numeric T, std::size_t Dims>
class Vector {
public:
    constexpr Vector() = default;
    constexpr Vector(T value) { elems_.fill(value); }
    constexpr Vector(const std::array<T, Dims> values)
        : elems_ { values } { }

    static constexpr Vector zero() noexcept { return { 0 }; }
    static constexpr Vector unit() noexcept { return { 1 }; }

    T &operator[](std::size_t idx) { return elems_[idx]; }

    constexpr auto operator-() const noexcept {
        Vector ret;
        std::transform(elems_.begin(), elems_.end(), ret.elems_.begin(), [](auto v) { return -v; });
        return ret;
    }

    friend constexpr bool operator==(const Vector &lhs, const Vector &rhs) {
        return lhs.elems_ == rhs.elems_;
    }

private:
    std::array<T, Dims> elems_ {};
};

// Non-owning type used for math operations
template <Numeric T, std::size_t Dims>
class RowVector {
public:
    RowVector() = delete;

private:
    std::span<T, Dims> elems_;
};

} // namespace dk::math

#endif
