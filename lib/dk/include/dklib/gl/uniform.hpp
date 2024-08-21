#ifndef DK_GL_UNIFORM_HPP
#define DK_GL_UNIFORM_HPP

#include <GLES3/gl3.h>
#include <spdlog/spdlog.h>

#include <span>
#include <string>
#include <utility>

#include <dklib/concepts.h>
#include <dklib/gl/gltypes.hpp>

namespace dk::gl {

class Uniform {
public:
    Uniform(i32 location, std::string &&name)
        : location_(location)
        , name_(std::move(name)) {};

    Uniform(i32 location, const std::string &name)
        : location_(location)
        , name_(name) {
        spdlog::info("Creating Uniform, name: {} location: {}", name_, location_);
    };

    Uniform(const Uniform &other)
        : Uniform(other.location_, other.name_) {};

    Uniform(Uniform &&other) noexcept
        : location_(std::move(other.location_))
        , name_(std::move(other.name_)) { }

    Uniform &operator=(const Uniform &other) {
        Uniform tmp(other);
        std::swap(*this, tmp);
        return *this;
    }

    Uniform &operator=(Uniform &&other) noexcept {
        std::swap(location_, other.location_);
        std::swap(name_, other.name_);
        return *this;
    }

    [[nodiscard]] gl::i32 get_location() const noexcept { return location_; }

    template <typename T, std::size_t H, std::size_t W>
    using mat = std::span<T, H * W>;

    inline void set(std::span<i32, 1> vec) const noexcept {
        glUniform1iv(location_, sizeof(i32), vec.data());
    };
    inline void set(std::span<u32, 1> vec) const noexcept {
        glUniform1uiv(location_, sizeof(u32), vec.data());
    };
    inline void set(std::span<f32, 1> vec) const noexcept {
        glUniform1fv(location_, sizeof(f32), vec.data());
    };
    inline void set(std::span<i32, 2> vec) const noexcept {
        glUniform2iv(location_, sizeof(i32) * 2, vec.data());
    };
    inline void set(std::span<u32, 2> vec) const noexcept {
        glUniform2uiv(location_, sizeof(u32) * 2, vec.data());
    };
    inline void set(std::span<f32, 2> vec) const noexcept {
        glUniform2fv(location_, sizeof(f32) * 2, vec.data());
    };
    inline void set(std::span<i32, 3> vec) const noexcept {
        glUniform3iv(location_, sizeof(i32) * 3, vec.data());
    };
    inline void set(std::span<u32, 3> vec) const noexcept {
        glUniform3uiv(location_, sizeof(u32) * 3, vec.data());
    };
    inline void set(std::span<f32, 3> vec) const noexcept {
        glUniform3fv(location_, sizeof(f32) * 3, vec.data());
    };
    inline void set(std::span<i32, 4> vec) const noexcept {
        glUniform4iv(location_, sizeof(i32) * 4, vec.data());
    };
    inline void set(std::span<u32, 4> vec) const noexcept {
        glUniform4uiv(location_, sizeof(u32) * 4, vec.data());
    };
    inline void set(std::span<f32, 4> vec) const noexcept {
        glUniform4fv(location_, sizeof(f32) * 4, vec.data());
    };

    inline void set(mat<f32, 4, 4> mat, bool transpose = false) const noexcept {
        glUniformMatrix4fv(location_, 1, static_cast<GLboolean>(transpose), mat.data());
    };

    inline void set(u32 x) const noexcept { glUniform1ui(location_, x); };
    inline void set(i32 x) const noexcept { glUniform1i(location_, x); };
    inline void set(f32 x) const noexcept { glUniform1f(location_, x); };
    inline void set(u32 x, u32 y) const noexcept {
        glUniform2ui(location_, x, y);
    };
    inline void set(i32 x, i32 y) const noexcept {
        glUniform2i(location_, x, y);
    };
    inline void set(f32 x, f32 y) const noexcept {
        glUniform2f(location_, x, y);
    };
    inline void set(u32 x, u32 y, u32 z) const noexcept {
        glUniform3ui(location_, x, y, z);
    };
    inline void set(i32 x, i32 y, i32 z) const noexcept {
        glUniform3i(location_, x, y, z);
    };
    inline void set(f32 x, f32 y, f32 z) const noexcept {
        glUniform3f(location_, x, y, z);
    };
    inline void set(u32 x, u32 y, u32 z, u32 w) const noexcept {
        glUniform4ui(location_, x, y, z, w);
    };
    inline void set(i32 x, i32 y, i32 z, i32 w) const noexcept {
        glUniform4i(location_, x, y, z, w);
    };
    inline void set(f32 x, f32 y, f32 z, f32 w) const noexcept {
        glUniform4f(location_, x, y, z, w);
    };

private:
    i32 location_;
    std::string name_;
};
} // namespace dk::gl

#endif // DK_GL_UNIFORM_HPP
