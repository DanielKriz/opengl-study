#ifndef DK_OPENGL_PROGRAM_HPP
#define DK_OPENGL_PROGRAM_HPP

#include "gltypes.hpp"
#include "shader.hpp"
#include "uniform.hpp"

#include <dklib/util.h>

#include <GLES3/gl3.h>
#include <spdlog/spdlog.h>

#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

namespace dk::gl {
class Program {
public:
    Program();
    virtual ~Program();

    template <typename... Args>
    Program &attach_shader(Args &&...args) {
        shaders_.emplace_back(std::forward<Args>(args)...);
        auto owned = shaders_.back().get();
        glAttachShader(program_descriptor_, owned);

        gl::i32 is_compilation_success = -1;
        glGetShaderiv(owned, GL_COMPILE_STATUS, &is_compilation_success);
        if (not static_cast<bool>(is_compilation_success)) {
            spdlog::error("Compilation of shader was not succesful");
            auto msg = util::get_shader_error_msg(owned);
            spdlog::error("shader log contents:\n {}", msg);
            throw std::runtime_error("compilation of shader was not successful");
        }
        return *this;
    }

    [[nodiscard]] gl::i32 get_uniform(const std::string &name) const;
    [[nodiscard]] gl::i32 get_attribute(const std::string &name) const;

    [[nodiscard]] gl::Uniform get_uniform(bool t, const std::string &name);
    [[nodiscard]] gl::i32 get_attribute(bool t, const std::string &name) const;

    Program &link();
    void use() const;

    void populate_attributes();
    void populate_uniforms();

    [[nodiscard]] gl::u32 get_id() const noexcept { return program_descriptor_; }

private:
    std::vector<gl::Shader> shaders_;
    gl::u32 program_descriptor_;
    gl::u32 vertex_array_id_;
    gl::i32 uniforms_;
    std::unordered_map<std::string, gl::Uniform> uniform_cache_;
};
} // namespace dk::gl
#endif // DK_OPENGL_PROGRAM_HPP
