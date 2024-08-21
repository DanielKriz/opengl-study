#include "triangle.hpp"

namespace dk {
SimpleCubeApplication::SimpleCubeApplication()
    : Application("Simple Cube")
    , program() {
    spdlog::info("current file: {}", std::filesystem::current_path().c_str());
    program
        .attach_shader("src/simple_cube/fshader.glsl", gl::ShaderType::FRAGMENT)
        .attach_shader("src/simple_cube/vshader.glsl", gl::ShaderType::VERTEX)
        .link();
    glGenVertexArrays(1, &vao);
};

SimpleCubeApplication::~SimpleCubeApplication() {
    glDeleteVertexArrays(1, &vao);
    spdlog::info("correctly cleaning up");
}

} // namespace dk

DECLARE_MAIN(dk::SimpleCubeApplication);
