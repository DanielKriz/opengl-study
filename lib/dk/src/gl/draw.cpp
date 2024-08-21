#include <dklib/gl/draw.hpp>

namespace dk::gl {

void draw(DrawMode mode, gl::size offset, gl::size count) {
    glDrawArrays(static_cast<gl::enum32>(mode), offset, count);
}
} // namespace dk::gl
