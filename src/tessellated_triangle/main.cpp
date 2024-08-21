#include "triangle.hpp"

namespace dk {
TessellatedTriangleApplication::TessellatedTriangleApplication()
    : Application("Tessellated Triangle")
    , program() {
    spdlog::info("current file: {}", std::filesystem::current_path().c_str());
    program
        .attach_shader("src/tessellated_triangle/fshader.glsl", gl::ShaderType::FRAGMENT)
        .attach_shader("src/tessellated_triangle/vshader.glsl", gl::ShaderType::VERTEX)
        .attach_shader("src/tessellated_triangle/tess_ctrl.glsl", gl::ShaderType::TESS_CONTROL)
        .attach_shader("src/tessellated_triangle/tess_eval.glsl", gl::ShaderType::TESS_EVALUATION)
        .link();
    glGenVertexArrays(1, &vao);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
};

TessellatedTriangleApplication::~TessellatedTriangleApplication() {
    glDeleteVertexArrays(1, &vao);
}

} // namespace dk

DECLARE_MAIN(dk::TessellatedTriangleApplication);
