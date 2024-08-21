#ifndef DK_GL_VERTEX_HPP
#define DK_GL_VERTEX_HPP

#include <type_traits>

#include <GLES3/gl3.h>

#include <dklib/gl/gltypes.hpp>
#include <dklib/math/vector3d.hpp>

namespace dk::gl {

namespace experimental {

    struct PositionalVertex {
        math::Vector3D position;
    };

    // FIXME: this is going to fail until vector is not trivially copyable
    // static_assert(std::is_trivially_copyable_v<PositionalVertex>, "Vertex type
    // should be trivially copyable!");
    static_assert(std::is_standard_layout_v<PositionalVertex>, "Vertex type should have standard layout");

    struct TexturingVertex {
        math::Vector3D position;
        f32 u;
        f32 v;
    };
    static_assert(std::is_standard_layout_v<TexturingVertex>, "Vertex type should have standard layout");

    struct Vertex {
        math::Vector3D position;
        math::Vector3D normal;
        f32 u;
        f32 v;
    };

    template <typename T>
    inline void *offset_cast(u32 offset) {
        return reinterpret_cast<void *>(offset * sizeof(T));
    }

    template <typename T>
    inline void bind_attributes_v2(u32 layout_idx) {
        glVertexAttribPointer(layout_idx, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), offset_cast<f32>(0));
        glVertexAttribPointer(layout_idx + 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), offset_cast<f32>(3));
        glVertexAttribPointer(layout_idx + 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), offset_cast<f32>(6));
    }

    static_assert(std::is_standard_layout_v<Vertex>, "Vertex type should have standard layout");

} // namespace experimental

struct Vertex {
    f32 position[3];
    f32 u;
    f32 v;
};

inline void bind_attributes(u32 layout_idx) {
    glVertexAttribPointer(layout_idx, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

} // namespace dk::gl

#endif // DK_GL_VERTEX_HPP
