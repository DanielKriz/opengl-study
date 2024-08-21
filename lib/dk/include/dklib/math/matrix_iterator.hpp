#ifndef DK_MATH_MATRIX_ITERATOR_HPP
#define DK_MATH_MATRIX_ITERATOR_HPP

#include <iterator>

#include <dklib/math/math_concepts.hpp>

namespace dk::math {

template <Numeric T>
class MatrixIterator {
public:
    using iterator_concept = std::contiguous_iterator_tag;
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using size_type = std::size_t;
    using value_type = std::remove_const_t<T>;
    using pointer = T *;
    using reference = T &;
    using self_type = MatrixIterator;

    constexpr MatrixIterator() noexcept = default;
    constexpr explicit MatrixIterator(pointer ptr, size_type offset = 0) noexcept
        : ptr_(ptr + offset) {};
    constexpr ~MatrixIterator() = default;

    constexpr MatrixIterator(const self_type &other) = default;
    constexpr MatrixIterator &operator=(const self_type &other) = default;

    constexpr MatrixIterator(self_type &&other) noexcept = default;
    constexpr MatrixIterator &operator=(self_type &&other) noexcept = default;

    constexpr reference operator*() const noexcept { return *ptr_; }
    constexpr reference operator->() const noexcept { return ptr_; }
    constexpr self_type &operator++() noexcept {
        ++ptr_;
        return *this;
    }
    constexpr self_type operator++(int) noexcept {
        auto tmp = *this;
        ++ptr_;
        return tmp;
    }
    constexpr self_type &operator--() noexcept {
        --ptr_;
        return *this;
    }
    constexpr self_type operator--(int) noexcept {
        auto tmp = *this;
        --ptr_;
        return tmp;
    }
    constexpr self_type &operator+=(const difference_type offset) noexcept {
        ptr_ += offset;
        return *this;
    }

    constexpr self_type operator+(const difference_type offset) noexcept {
        auto tmp = *this;
        return tmp += offset;
    }
    constexpr self_type &operator-=(const difference_type offset) noexcept {
        ptr_ -= offset;
        return *this;
    }
    constexpr self_type operator-(const difference_type offset) noexcept {
        auto tmp = *this;
        return tmp -= offset;
    }
    constexpr difference_type operator-(const self_type &other) noexcept {
        return ptr_ - other.ptr_;
    }
    constexpr reference operator[](const difference_type offset) const noexcept {
        return ptr_[offset];
    }
    constexpr std::strong_ordering
    operator<=>(const self_type &other) const noexcept {
        return ptr_ <=> other.ptr_;
    }

    friend constexpr bool operator==(const self_type &lhs, const self_type &rhs) noexcept = default;
    friend constexpr self_type operator+(const difference_type offset, self_type &rhs) noexcept {
        return rhs += offset;
    }

private:
    pointer ptr_;
};

static_assert(std::is_trivially_copyable_v<MatrixIterator<float>>, "Iterator should be trivially copyable");

template <Numeric T>
class MatrixStrideIterator {
public:
    using iterator_concept = std::contiguous_iterator_tag;
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using size_type = std::size_t;
    using value_type = std::remove_const_t<T>;
    using pointer = T *;
    using reference = T &;
    using self_type = MatrixStrideIterator;

    constexpr MatrixStrideIterator() noexcept = default;
    constexpr explicit MatrixStrideIterator(pointer ptr, size_type stride = 1, size_type offset = 0) noexcept
        : ptr_(ptr + offset)
        , stride_(stride) {};
    constexpr ~MatrixStrideIterator() = default;

    constexpr MatrixStrideIterator(const self_type &other) = default;
    constexpr MatrixStrideIterator &operator=(const self_type &other) = default;

    constexpr MatrixStrideIterator(self_type &&other) noexcept = default;
    constexpr MatrixStrideIterator &
    operator=(self_type &&other) noexcept
        = default;

    constexpr reference operator*() const noexcept { return *ptr_; }
    constexpr reference operator->() const noexcept { return ptr_; }
    constexpr self_type &operator++() noexcept {
        ptr_ += stride_;
        return *this;
    }
    constexpr self_type operator++(int) noexcept {
        auto tmp = *this;
        ptr_ += stride_;
        return tmp;
    }
    constexpr self_type &operator--() noexcept {
        ptr_ -= stride_;
        return *this;
    }
    constexpr self_type operator--(int) noexcept {
        auto tmp = *this;
        ptr_ -= stride_;
        return tmp;
    }
    constexpr self_type &operator+=(const difference_type offset) noexcept {
        ptr_ += offset * stride_;
        return *this;
    }

    constexpr self_type operator+(const difference_type offset) noexcept {
        auto tmp = *this;
        return tmp += offset * stride_;
    }
    constexpr self_type &operator-=(const difference_type offset) noexcept {
        ptr_ -= offset * stride_;
        return *this;
    }
    constexpr self_type operator-(const difference_type offset) noexcept {
        auto tmp = *this;
        return tmp -= offset * stride_;
    }
    constexpr difference_type operator-(const self_type &other) noexcept {
        return ptr_ - other.ptr_;
    }
    constexpr reference operator[](const difference_type offset) const noexcept {
        return ptr_[offset * stride_];
    }
    constexpr std::strong_ordering
    operator<=>(const self_type &other) const noexcept {
        return ptr_ <=> other.ptr_;
    }

    friend constexpr bool operator==(const self_type &lhs, const self_type &rhs) noexcept {
        return lhs.ptr_ == rhs.ptr_;
    }

    friend constexpr self_type operator+(const difference_type offset, self_type &rhs) noexcept {
        return rhs += offset;
    }

private:
    pointer ptr_;
    size_type stride_ { 1 };
};

static_assert(std::is_trivially_copyable_v<MatrixStrideIterator<float>>, "Iterator should be trivially copyable");

template <Numeric T>
using MatrixRowIterator = MatrixStrideIterator<T>;

} // namespace dk::math

#endif // DK_MATH_MATRIX_ITERATOR_HPP
