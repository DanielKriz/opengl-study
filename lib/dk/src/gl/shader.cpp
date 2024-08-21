#include <dklib/gl/shader.hpp>

namespace dk::gl {
Shader::Shader(std::string &&filepath, gl::ShaderType type) {
    descriptor_ = glCreateShader(static_cast<GLenum>(type));
    get_source_from_file(std::forward<std::string>(filepath));
    const char *c_str = str_source.c_str();
    glShaderSource(descriptor_, 1, &c_str, nullptr);
    glCompileShader(descriptor_);
}

Shader::~Shader() {
    // WARNING: this can be done much earlier, basically in the moment that
    // program is linked, perhaps I could add something to the link() function.
    glDeleteShader(descriptor_);
}

} // namespace dk::gl
