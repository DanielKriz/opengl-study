#include <dklib/util/string_util.hpp>

namespace dk::util {
std::vector<std::string> split_by_delimeter(const std::string &str, const char *delim) {
    // std::size_t pos;
    // std::size_t end = 0;
    std::vector<std::string> out;

    // while ((pos = str.find(delim)) != std::string::npos) {
    //     out.emplace_back(str.substr(0, pos));
    //     str.erase(0, pos + std::strlen(delim));
    // }

    std::size_t prev = 0;
    std::size_t pos = 0;
    do {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) {
            pos = str.length();
        }
        out.emplace_back(str.substr(prev, pos - prev));
        prev = pos + std::strlen(delim);
    } while (pos < str.length() and prev < str.length());
    // std::cout << "this da problem" << std::endl;
    return out;
}

std::vector<int> strs_to_ints(const std::vector<std::string> &strs) {
    std::vector<int> out;
    out.reserve(strs.size());
    // std::cout << "no, diz da problem" << std::endl;
    for (const auto &str : strs) {
        out.emplace_back(str.empty() ? 0 : std::stoi(str));
    }
    // std::cout << "no you wazuk" << std::endl;
    return out;
}

std::vector<float> strs_to_floats(const std::vector<std::string> &strs) {
    std::vector<float> out;
    out.reserve(strs.size());
    for (const auto &str : strs) {
        out.emplace_back(std::stof(str));
    }
    return out;
}

} // namespace dk::util
