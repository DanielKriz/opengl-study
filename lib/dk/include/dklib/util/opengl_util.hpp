#ifndef DK_OPENGL_UTIL_HPP
#define DK_OPENGL_UTIL_HPP

#include <dklib/gl/gltypes.hpp>

#include <GLES3/gl3.h>
#include <spdlog/spdlog.h>
#include <string>

#define DECLARE_MAIN(AppType)                                                  \
    int main([[maybe_unused]] int argc, [[maybe_unused]] const char *argv[]) { \
        AppType app {};                                                        \
        app.run(app);                                                          \
        return 0;                                                              \
    }

namespace dk::util {
std::string get_shader_error_msg(gl::u32 shader_descriptor);
} // namespace dk::util

#endif // DK_OPENGL_UTIL_HPP
