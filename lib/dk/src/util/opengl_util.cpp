#include <dklib/util/opengl_util.hpp>

namespace dk::util {
std::string get_shader_error_msg(gl::u32 descriptor) {
    gl::size log_size = 0;
    glGetShaderiv(descriptor, GL_INFO_LOG_LENGTH, &log_size);

    std::string retval {};
    retval.resize(static_cast<gl::u32>(log_size));

    glGetShaderInfoLog(descriptor, log_size, nullptr, retval.data());
    if (glGetError() != 0) {
        spdlog::error("Getting information about shader failed with code {}", glGetError());
        throw std::runtime_error("Getting information about shader failed");
    }
    return retval;
}

} // namespace dk::util
