#ifndef DK_GL_CONCEPTS_HPP
#define DK_GL_CONCEPTS_HPP

#include <concepts>
#include <type_traits>

#include <dklib/math/vmath.h>

namespace dk::gl {

template <typename T>
concept ContiguousMemoryContainer = requires(T container) {
    {
        container.data()
    } -> std::convertible_to<T *>;
};

template <typename T>
concept Uniformable = std::integral<T> or std::floating_point<T> or std::is_base_of<vmath::Tmat4<T>, T>::value or ContiguousMemoryContainer<T>;
} // namespace dk::gl

#endif // DK_GL_CONCEPTS_HPP
