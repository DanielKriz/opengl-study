#ifndef DK_STRING_UTIL_HPP
#define DK_STRING_UTIL_HPP

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

namespace dk::util {
std::vector<std::string> split_by_delimeter(const std::string &str, const char *delim);
std::vector<int> strs_to_ints(const std::vector<std::string> &strs);
std::vector<float> strs_to_floats(const std::vector<std::string> &strs);
} // namespace dk::util

#endif // DK_STRING_UTIL_HPP
