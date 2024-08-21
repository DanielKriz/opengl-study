#include "triangle.hpp"

namespace dk {
TrueTriangleApplication::TrueTriangleApplication()
    : Application("True Triangle")
    , program() {
    spdlog::info("current file: {}", std::filesystem::current_path().c_str());
    program
        .attach_shader("src/true_triangle/fshader.glsl", gl::ShaderType::FRAGMENT)
        .attach_shader("src/true_triangle/vshader.glsl", gl::ShaderType::VERTEX)
        .link();
};

TrueTriangleApplication::~TrueTriangleApplication() {
    spdlog::info("correctly cleaning up");
}

} // namespace dk

DECLARE_MAIN(dk::TrueTriangleApplication);
