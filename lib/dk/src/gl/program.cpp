#include <dklib/gl/program.hpp>

namespace dk::gl {
Program::Program()
    : program_descriptor_(glCreateProgram()) { }

Program::~Program() {
    glDeleteVertexArrays(1, &vertex_array_id_);
    glDeleteProgram(program_descriptor_);
}

Program &Program::link() {
    glLinkProgram(program_descriptor_);
    glGenVertexArrays(1, &vertex_array_id_);
    glBindVertexArray(vertex_array_id_);
    return *this;
}

[[nodiscard]] gl::i32 Program::get_uniform(const std::string &name) const {
    if (auto it = uniform_cache_.find(name); it != uniform_cache_.end()) {
        return it->second.get_location();
    }
    auto location = glGetUniformLocation(program_descriptor_, name.c_str());
    if (location < 0) {
        spdlog::error("Could not get uniform location of '{}'", name);
        throw std::runtime_error("Could not get uniform location");
    }
    return location;
}

// NOTE: this is unusable until we have some real matrix type
[[nodiscard]] gl::Uniform Program::get_uniform(bool t, const std::string &name) {
    if (auto it = uniform_cache_.find(name); it != uniform_cache_.end()) {
        return it->second;
    }
    auto location = glGetUniformLocation(program_descriptor_, name.data());
    if (location < 0) {
        spdlog::error("Could not get uniform location of '{}'", name);
        throw std::runtime_error("Could not get uniform location");
    }
    auto uniform = uniform_cache_.try_emplace(name, location, name);
    return uniform.first->second;
}

[[nodiscard]] gl::i32 Program::get_attribute(const std::string &name) const {
    if (auto it = uniform_cache_.find(name); it != uniform_cache_.end()) {
        return it->second.get_location();
    }
    auto location = glGetUniformLocation(program_descriptor_, name.data());
    if (location < 0) {
        spdlog::error("Could not get uniform location of '{}'", name);
        throw std::runtime_error("Could not get uniform location");
    }
    return location;
}

void Program::use() const { glUseProgram(program_descriptor_); }

} // namespace dk::gl
