#ifndef DK_OPENGL_SHADER_HPP
#define DK_OPENGL_SHADER_HPP

#include "gltypes.hpp"

#include <GLES3/gl3.h>
#include <spdlog/spdlog.h>

#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <span>
#include <sstream>
#include <string>

namespace dk::gl {
enum class ShaderType : gl::enum32 {
    FRAGMENT = GL_FRAGMENT_SHADER,
    VERTEX = GL_VERTEX_SHADER,
    TESS_CONTROL = GL_TESS_CONTROL_SHADER,
    TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
    GEOMETRY = GL_GEOMETRY_SHADER,
    COMPUTE = GL_COMPUTE_SHADER,
};

class Shader {
public:
    // TODO: add third default arugment "use_base_shader_path" or something
    // like that, it is going to define common prefix
    Shader(std::string &&filepath, gl::ShaderType type);
    virtual ~Shader();

    // TODO: try these new types on more places
    [[nodiscard]] inline gl::u32 get() const { return descriptor_; }

private:
    void get_source_from_file(std::string &&filepath) {
        spdlog::info("attaching shader with filepath: {}", filepath);
        std::ifstream file(filepath);
        if (not file.is_open()) {
            spdlog::error("file: {} could not be opened", filepath);
            throw std::runtime_error("could not open file");
        }

        std::ostringstream ss;
        ss << file.rdbuf();
        str_source = ss.str();
        std::cout << str_source << std::endl;
    }
    std::string str_source;
    gl::u32 descriptor_;
};
} // namespace dk::gl
#endif // DK_OPENGL_SHADER_HPP
