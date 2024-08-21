#include "triangle.hpp"

namespace dk {
GeometryApplication::GeometryApplication()
    : Application("Tessellated Triangle")
    , program() {
    spdlog::info("current file: {}", std::filesystem::current_path().c_str());
    program
        .attach_shader("src/first_geometry_shader/fshader.glsl", gl::ShaderType::FRAGMENT)
        .attach_shader("src/first_geometry_shader/vshader.glsl", gl::ShaderType::VERTEX)
        .attach_shader("src/first_geometry_shader/tess_ctrl.glsl", gl::ShaderType::TESS_CONTROL)
        .attach_shader("src/first_geometry_shader/tess_eval.glsl", gl::ShaderType::TESS_EVALUATION)
        .attach_shader("src/first_geometry_shader/gshader.glsl", gl::ShaderType::GEOMETRY)
        .link();
    glGenVertexArrays(1, &vao);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
};

GeometryApplication::~GeometryApplication() { glDeleteVertexArrays(1, &vao); }

} // namespace dk

DECLARE_MAIN(dk::GeometryApplication);
