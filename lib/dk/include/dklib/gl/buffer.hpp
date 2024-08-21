#ifndef DK_OPENGL_BUFFER_HPP
#define DK_OPENGL_BUFFER_HPP

#include <GLES3/gl3.h>
#include <iostream>
#include <map>
#include <unordered_map>

#include "gltypes.hpp"

namespace dk::gl {
enum class BufferType : gl::enum32 {
    COLOR = GL_COLOR,
    DEPTH = GL_DEPTH,
    STENCIL = GL_STENCIL,
};

namespace {
    const std::unordered_map<BufferType, gl::enum32> buffer_bit_map = {
        { BufferType::COLOR, GL_COLOR_BUFFER_BIT },
        { BufferType::DEPTH, GL_DEPTH_BUFFER_BIT },
        { BufferType::STENCIL, GL_STENCIL_BUFFER_BIT },
    };
}

inline BufferType operator|(const BufferType lhs, const BufferType rhs) {
    return static_cast<BufferType>(buffer_bit_map.at(lhs) | buffer_bit_map.at(rhs));
}

inline void clear_buffers(BufferType buffers_to_clear_flag) {
    glClear(static_cast<gl::u32>(buffers_to_clear_flag));
}

class ColorBuffer {
public:
    template <typename T>
    static void clear(gl::i32 draw_buffer_index, const T *value);
};

template <typename T>
void ColorBuffer::clear(gl::i32 draw_buffer_index, const T *value) {
    glClearBufferfv(static_cast<gl::u32>(BufferType::COLOR), draw_buffer_index, value);
}

class DepthBuffer {
public:
    template <typename T>
    static void clear(gl::i32 draw_buffer_index, const T *value);
    template <typename T>
    static void clear(gl::i32 draw_buffer_index);
};

template <typename T>
void DepthBuffer::clear(gl::i32 draw_buffer_index, const T *value) {
    glClearBufferfv(static_cast<gl::u32>(BufferType::DEPTH), draw_buffer_index, value);
}

template <typename T>
void DepthBuffer::clear(gl::i32 draw_buffer_index) {
    static const gl::f32 ONE = 1.0f;
    glClearBufferfv(static_cast<gl::u32>(BufferType::DEPTH), draw_buffer_index, &ONE);
}

class StencilBuffer {
public:
    template <typename T>
    static void clear(gl::i32 draw_buffer_index, const T *value);
};

template <typename T>
void StencilBuffer::clear(gl::i32 draw_buffer_index, const T *value) {
    glClearBufferfv(static_cast<gl::u32>(BufferType::STENCIL), draw_buffer_index, value);
}
} // namespace dk::gl

#endif // DK_OPENGL_BUFFER_HPP
