#ifndef DK_VARIANT_UTIL_HPP
#define DK_VARIANT_UTIL_HPP

namespace dk::util {

template <class... Ts>
struct overload : Ts... {
    using Ts::operator()...;
};
template <class... Ts>
overload(Ts...) -> overload<Ts...>;

} // namespace dk::util

#endif // DK_VARIANT_UTIL_HPP
