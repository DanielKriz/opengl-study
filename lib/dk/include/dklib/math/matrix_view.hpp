#ifndef DK_MATH_MATRIX_VIEW_HPP
#define DK_MATH_MATRIX_VIEW_HPP

#include <iterator>

#include <dklib/math/math_concepts.hpp>
#include <dklib/math/matrix_iterator.hpp>

namespace dk::math {

template <Numeric T>
class MatrixView {
public:
    using size_type = std::size_t;
    using value_type = std::remove_const_t<T>;
    using pointer = T *;
    using reference = T &;
    using self_type = MatrixView;

    using iterator = MatrixIterator<T>;
    using const_iterator = MatrixIterator<const T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    constexpr MatrixView() noexcept = default;
    constexpr MatrixView(pointer ptr, size_type rows, size_type cols) noexcept {};

    constexpr ~MatrixView() noexcept = default;

    constexpr MatrixView(const MatrixView<value_type> &) = default;
    constexpr MatrixView &operator=(const MatrixView<value_type> &mat)
    requires(not std::is_const_v<T>)
    {
        return {};
    }

    pointer data() noexcept { return {}; }

    constexpr iterator begin() noexcept
    requires(not std::is_const_v<T>)
    {
        return {};
    }
    constexpr iterator end() noexcept
    requires(not std::is_const_v<T>)
    {
        return {};
    }

    constexpr iterator cbegin() const noexcept { return {}; }
    constexpr iterator cend() const noexcept { return {}; }

    constexpr iterator rbegin() noexcept
    requires(not std::is_const_v<T>)
    {
        return {};
    }
    constexpr iterator rend() noexcept
    requires(not std::is_const_v<T>)
    {
        return {};
    }

    constexpr iterator crbegin() const noexcept { return {}; }
    constexpr iterator crend() const noexcept { return {}; }

    [[nodiscard]] constexpr size_type rows() const noexcept { return {}; }
    [[nodiscard]] constexpr size_type cols() const noexcept { return {}; }

private:
    pointer ptr_ {};
    size_type rows_ {};
    size_type cols_ {};
};
} // namespace dk::math

#endif // DK_MATH_MATRIX_VIEW_HPP
