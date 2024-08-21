#ifndef DK_OPENGL_DRAW_HPP
#define DK_OPENGL_DRAW_HPP

#include "gltypes.hpp"

#include <GLES3/gl3.h>

#include <utility>

namespace dk::gl {
enum class DrawMode : gl::enum32 {
    TRIANGLES = GL_TRIANGLES,
};
void draw(DrawMode mode, gl::size offset, gl::size count);
} // namespace dk::gl

#endif // DK_OPENGL_DRAW_HPP
