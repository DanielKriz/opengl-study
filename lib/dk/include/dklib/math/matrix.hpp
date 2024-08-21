#ifndef DK_MATH_MATRIX_HPP
#define DK_MATH_MATRIX_HPP

#include <array>
#include <cmath>
#include <iterator>
#include <type_traits>

#include <fmt/format.h>

#include <dklib/math/math_concepts.hpp>
#include <dklib/math/matrix_iterator.hpp>
#include <dklib/math/matrix_view.hpp>
#include <dklib/math/vector3d.hpp>

namespace dk::math {

template <Numeric T, std::size_t Rows, std::size_t Cols>
requires(PositiveNumber<Rows> and PositiveNumber<Cols>)
class Matrix {
public:
    using value_type = T;
    using pointer_type = T *;
    using reference_type = T &;
    using storage_type = std::array<value_type, Rows * Cols>;
    using storage_type_2d = std::array<std::array<value_type, Cols>, Rows>;
    using vector_type = Vector<value_type, Cols>;

    using iterator = MatrixIterator<value_type>;
    using const_iterator = MatrixIterator<const value_type>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // Constructors

    constexpr Matrix() = default;
    explicit constexpr Matrix(const float &value) { fill(value); }

    explicit(false) constexpr Matrix(const storage_type &in_elems)
        : elems_(in_elems) { }

    explicit(false) constexpr Matrix(const storage_type_2d &in_elems)
        : elems_ {} {
        std::size_t i = 0;
        for (const auto &row : in_elems) {
            for (const auto value : row) {
                elems_[i] = value;
                i++;
            }
        }
    }

    explicit constexpr Matrix(storage_type &&in_elems) noexcept
        : elems_(std::move(in_elems)) {};

    // Factory Methods

    static Matrix zero()
    requires SymmetricMatrix<Rows, Cols>
    {
        return Matrix(0);
    }

    static Matrix identity()
    requires SymmetricMatrix<Rows, Cols>
    {
        return {};
    }

    static Matrix diagonal(value_type value)
    requires SymmetricMatrix<Rows, Cols>
    {
        return {};
    }

    static Matrix diagonal(std::array<value_type, Cols> values)
    requires SymmetricMatrix<Rows, Cols>
    {
        return {};
    }

    static Matrix diagonal(vector_type vec)
    requires SymmetricMatrix<Rows, Cols>
    {
        return {};
    }

    static Matrix anti_diagonal(value_type value)
    requires SymmetricMatrix<Rows, Cols>
    {
        return {};
    }

    static Matrix anti_diagonal(std::array<value_type, Cols> values)
    requires SymmetricMatrix<Rows, Cols>
    {
        return {};
    }

    static Matrix anti_diagonal(vector_type vec)
    requires SymmetricMatrix<Rows, Cols>
    {
        return {};
    }

    static Matrix translate()
    requires TransormMatrix<Rows, Cols>
    {
        return {};
    }

    static Matrix look_at()
    requires TransormMatrix<Rows, Cols>
    {
        return {};
    }

    static Matrix rotation()
    requires TransormMatrix<Rows, Cols>;

    static Matrix scale(float scale_factor)
    requires SymmetricMatrix<Rows, Cols>
    {
        return {};
    }

    static Matrix scale(std::array<value_type, Cols> scale_factors)
    requires SymmetricMatrix<Rows, Cols>
    {
        return {};
    }

    static Matrix scale(vector_type scale_factors)
    requires SymmetricMatrix<Rows, Cols>
    {
        return {};
    }

    static Matrix skew()
    requires TransormMatrix<Rows, Cols>
    {
        return {};
    }

    static Matrix projection()
    requires TransormMatrix<Rows, Cols>
    {
        return {};
    }

    static Matrix reflect()
    requires TransormMatrix<Rows, Cols>
    {
        return {};
    }

    static Matrix retract()
    requires TransormMatrix<Rows, Cols>
    {
        return {};
    }

    // Predicates

    [[nodiscard]] bool is_zero() const noexcept { return {}; }
    [[nodiscard]] bool is_identity() const noexcept { return {}; }

    // Accessors

    [[nodiscard]] constexpr reference_type operator[](std::size_t idx) noexcept {
        return elems_[idx];
    }
    [[nodiscard]] constexpr value_type
    operator[](std::size_t idx) const noexcept {
        return elems_[idx];
    }

    [[nodiscard]] constexpr reference_type operator[](std::size_t x, std::size_t y) noexcept {
        return elems_[x * cols() + y];
    }
    [[nodiscard]] constexpr value_type operator[](std::size_t x, std::size_t y) const noexcept {
        return elems_[x * cols() + y];
    }

    [[nodiscard]] constexpr reference_type at(std::size_t x, std::size_t y) {
        if (x > Rows) {
            throw std::runtime_error("error 1");
        }
        return elems_[x * cols() + y];
    }
    [[nodiscard]] constexpr reference_type at(std::size_t x, std::size_t y) const {
        return elems_[x * cols() + y];
    }

    // Methods

    Matrix &fill(const float &value) {
        for (auto &ref : elems_) {
            ref = value;
        }
        return *this;
    }

    template <std::size_t Cols1, std::size_t Rows1>
    Matrix<T, Cols1, Rows1> reshape(std::size_t new_cols, std::size_t new_rows) {
        return {};
    }

    [[nodiscard]] constexpr std::size_t rows() const noexcept { return Rows; }
    [[nodiscard]] constexpr std::size_t cols() const noexcept { return Cols; }
    [[nodiscard]] constexpr std::size_t size() const noexcept {
        return Rows * Cols;
    }

    [[nodiscard]] constexpr pointer_type data() noexcept { return elems_.data(); }
    [[nodiscard]] constexpr pointer_type data() const noexcept {
        return const_cast<pointer_type>(elems_.data());
    }

    [[nodiscard]] constexpr Matrix<T, Cols, Rows> transpose() const { return {}; }

    // This method implements gauss method of computing determinant of matrix
    // base upon this post:
    // https://cs.stackexchange.com/questions/124759/determinant-calculation-bareiss-vs-gauss-algorithm
    [[nodiscard]] constexpr T determinant() const {
        auto &mat = *this;
        std::size_t n = mat.size();
        int sign = 1;
        for (int i = 0; i < (n - 1); ++i) {
            if (mat[i, i] == 0) {
                int m = 0;
                for (m = i + 1; m < n; ++m) {
                    if (mat[m, i] != 0) {
                        std::swap(mat[m], mat[i]);
                        sign = -sign;
                        break;
                    }
                }

                if (m == n) {
                    return 0;
                }
            }
            for (int j = i + 1; j < n; ++j) {
                const double ratio = mat[j, i] / mat[i, i];
                for (int k = 0; k < n; ++k) {
                    mat[j, k] -= ratio * mat[i, k];
                }
            }
        }

        double solution = 1;
        for (int i = 0; i < n; ++i) {
            solution *= mat[i, i];
        }
        return sign * solution;
    }
    friend constexpr T determinant(const Matrix &matrix) {
        return matrix.determinant();
    };

    // Iteration

    template <typename F>
    requires std::is_invocable_v<F, value_type>
    Matrix &for_each_elem(F func) {
        return *this;
    }

    template <typename F>
    requires std::is_invocable_v<F, vector_type>
    Matrix &for_each_row(F func) {
        return *this;
    }

    template <typename F>
    requires std::is_invocable_v<F, vector_type>
    Matrix &for_each_col(F func) {
        return *this;
    }

    [[nodiscard]] iterator begin() { return iterator { data(), 0 }; }
    [[nodiscard]] const_iterator begin() const {
        return const_iterator { data(), 0 };
    }
    [[nodiscard]] const_iterator cbegin() const { return begin(); }

    [[nodiscard]] iterator end() { return iterator { data(), elems_.size() }; }
    [[nodiscard]] const_iterator end() const {
        return const_iterator { data(), elems_.size() };
    }
    [[nodiscard]] const_iterator cend() const { return end(); }

    [[nodiscard]] reverse_iterator rbegin() { return reverse_iterator { end() }; }
    [[nodiscard]] const_reverse_iterator rbegin() const {
        return const_reverse_iterator { end() };
    }
    [[nodiscard]] const_reverse_iterator crbegin() const { return rbegin(); }

    [[nodiscard]] reverse_iterator rend() { return reverse_iterator { begin() }; }
    [[nodiscard]] const_reverse_iterator rend() const {
        return const_reverse_iterator { begin() };
    }
    [[nodiscard]] const_reverse_iterator crend() const { return rend(); }

    // Operators

    constexpr auto operator-() const noexcept { return *this; }

    constexpr auto &operator+=(T val) noexcept { return *this; }
    constexpr auto &operator-=(T val) noexcept { return *this; }
    constexpr auto &operator*=(T val) noexcept { return *this; }
    constexpr auto &operator%=(T val) { return *this; }
    constexpr auto &operator/=(T val) { return *this; }

    constexpr auto &operator+=(const vector_type &vec) noexcept { return *this; }
    constexpr auto &operator-=(const vector_type &vec) noexcept { return *this; }
    constexpr auto &operator*=(const vector_type &vec) noexcept { return *this; }
    constexpr auto &operator/=(const vector_type &vec) { return *this; }

    // TODO: add operations for row vectors
    // using row_vector_type = RowVector<T, Rows>;
    // constexpr auto &operator+=(const row_vector_type &vec) noexcept { return
    // *this; } constexpr auto &operator-=(const row_vector_type &vec) noexcept {
    // return *this; } constexpr auto &operator*=(const row_vector_type &vec)
    // noexcept { return *this; } constexpr auto &operator/=(const row_vector_type
    // &vec) { return *this; }

    constexpr auto &operator+=(const Matrix &mat) noexcept { return *this; }
    constexpr auto &operator-=(const Matrix &mat) noexcept { return *this; }

    friend constexpr Matrix operator+(const Matrix &mat, T val) noexcept {
        return {};
    }
    friend constexpr Matrix operator-(const Matrix &mat, T val) noexcept {
        return {};
    }
    friend constexpr Matrix operator*(const Matrix &mat, T val) noexcept {
        return {};
    }
    friend constexpr Matrix operator%(const Matrix &mat, T val) { return {}; }
    friend constexpr Matrix operator/(const Matrix &mat, T val) { return {}; }

    friend constexpr Matrix operator+(const Matrix &mat, const vector_type &vec) noexcept {
        return {};
    }
    friend constexpr Matrix operator-(const Matrix &mat, const vector_type &vec) noexcept {
        return {};
    }
    friend constexpr Matrix operator*(const Matrix &mat, const vector_type &vec) noexcept {
        return {};
    }
    friend constexpr Matrix operator/(const Matrix &mat, const vector_type &vec) {
        return {};
    }

    friend constexpr Matrix operator+(const Matrix &lhs, const Matrix &rhs) noexcept {
        return {};
    }
    friend constexpr Matrix operator-(const Matrix &lhs, const Matrix &rhs) noexcept {
        return {};
    }

    // template <typename T1, std::size_t R, std::size_t C>
    friend constexpr bool operator==(const Matrix &lhs, const Matrix &rhs) noexcept {
        return lhs.elems_ == rhs.elems_;
    };
    // friend constexpr Matrix operator-(const Matrix &lhs, const Matrix &rhs)
    // noexcept;

    // Compatibility and printing
    friend fmt::formatter<Matrix<T, Rows, Cols>>;
    friend std::ostream &operator<<(std::ostream &os, const Matrix &mat) {
        os << '(';
        bool is_first_row = true;
        for (std::size_t i = 0; i < Rows; ++i) {
            if (is_first_row) {
                is_first_row = false;
            } else {
                os << ',' << ' ';
            }
            os << '(';
            bool is_first = true;
            for (std::size_t j = 0; j < Cols; ++j) {
                if (is_first) {
                    is_first = false;
                } else {
                    os << ',' << ' ';
                }
                os << mat[i, j];
            }
            os << ')';
        }
        os << ')';
        return os;
    }

private:
    std::array<T, Rows * Cols> elems_;
};

} // namespace dk::math

#endif // DK_MATH_MATRIX_HPP
