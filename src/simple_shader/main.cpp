#include "simple_shader.hpp"
#include <filesystem>

namespace dk {
SimpleShaderApplication::SimpleShaderApplication()
    : Application("Simple Shader")
    , prog() {
    spdlog::info("current file: {}", std::filesystem::current_path().c_str());
    prog.attach_shader("src/simple_shader/fshader.glsl", gl::ShaderType::FRAGMENT)
        .attach_shader("src/simple_shader/vshader.glsl", gl::ShaderType::VERTEX)
        .link();
};

} // namespace dk

DECLARE_MAIN(dk::SimpleShaderApplication);
