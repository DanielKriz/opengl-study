#include "triangle.hpp"

namespace dk {
FirstTriangleApplication::FirstTriangleApplication()
    : Application("Simple Shader")
    , program() {
    spdlog::info("current file: {}", std::filesystem::current_path().c_str());
    program
        .attach_shader("src/first_triangle/fshader.glsl", gl::ShaderType::FRAGMENT)
        .attach_shader("src/first_triangle/vshader.glsl", gl::ShaderType::VERTEX)
        .link();
};

} // namespace dk

DECLARE_MAIN(dk::FirstTriangleApplication);
