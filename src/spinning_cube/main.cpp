#include <GL/gl.h>
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

#include <dklib/math.h>
#include <dklib/dklib.h>

#include <cmath>
#include <filesystem>
#include <fstream>
#include <string_view>

namespace dk {
class SpinningCubeApp : public dk::gl::Application {
public:
    SpinningCubeApp()
        : Application("Spinning Cube")
        , program()
        , aspect_ratio(static_cast<gl::f32>(info.window_width) / static_cast<gl::f32>(info.window_height)) {
        using namespace std::string_literals;
        spdlog::info("Current window width: {} and height: {}", info.window_width, info.window_height);
        const std::string path_prefix = "src/spinning_cube/"s;
        program
            .attach_shader(path_prefix + "base.fs.glsl", gl::ShaderType::FRAGMENT)
            .attach_shader(path_prefix + "base.vs.glsl", gl::ShaderType::VERTEX)
            .link();

        mv_location = program.get_uniform("mv_matrix");
        proj_location = program.get_uniform("proj_matrix");
        spdlog::info("mv: {}, proj: {}", mv_location, proj_location);

        proj_matrix = vmath::perspective(50.0f, aspect_ratio, 0.1f, 1000.0f);

        static const gl::f32 vertex_positions[] = {
            -0.25f, 0.25f, -0.25f, -0.25f, -0.25f, -0.25f, 0.25f, -0.25f, -0.25f,

            0.25f, -0.25f, -0.25f, 0.25f, 0.25f, -0.25f, -0.25f, 0.25f, -0.25f,

            0.25f, -0.25f, -0.25f, 0.25f, -0.25f, 0.25f, 0.25f, 0.25f, -0.25f,

            0.25f, -0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, -0.25f,

            0.25f, -0.25f, 0.25f, -0.25f, -0.25f, 0.25f, 0.25f, 0.25f, 0.25f,

            -0.25f, -0.25f, 0.25f, -0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f,

            -0.25f, -0.25f, 0.25f, -0.25f, -0.25f, -0.25f, -0.25f, 0.25f, 0.25f,

            -0.25f, -0.25f, -0.25f, -0.25f, 0.25f, -0.25f, -0.25f, 0.25f, 0.25f,

            -0.25f, -0.25f, 0.25f, 0.25f, -0.25f, 0.25f, 0.25f, -0.25f, -0.25f,

            0.25f, -0.25f, -0.25f, -0.25f, -0.25f, -0.25f, -0.25f, -0.25f, 0.25f,

            -0.25f, 0.25f, -0.25f, 0.25f, 0.25f, -0.25f, 0.25f, 0.25f, 0.25f,

            0.25f, 0.25f, 0.25f, -0.25f, 0.25f, 0.25f, -0.25f, 0.25f, -0.25f
        };

        glGenBuffers(1, &buf);
        glBindBuffer(GL_ARRAY_BUFFER, buf);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(0);

        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CW);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
    };
    virtual ~SpinningCubeApp() { glDeleteBuffers(1, &buf); };
    virtual void init() override {};
    virtual void startup() override {};
    virtual void render(double delta) override {
        static const gl::f32 green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
        static const gl::f32 one = 1.0f;

        glViewport(0, 0, info.window_width, info.window_height);
        glClearBufferfv(GL_COLOR, 0, green);
        glClearBufferfv(GL_DEPTH, 0, &one);

        program.use();
        // glUseProgram(program);

        glUniformMatrix4fv(proj_location, 1, GL_FALSE, proj_matrix);

        gl::f32 f = static_cast<gl::f32>(delta) * 0.3f;
        vmath::mat4 mv_matrix = vmath::translate(0.0f, 0.0f, -4.0f) * vmath::translate(sinf(2.1f * f) * 0.5f, cosf(1.7f * f) * 0.5f, sinf(1.3f * f) * cosf(1.5f * f) * 2.0f) * vmath::rotate(static_cast<gl::f32>(delta) * 45.0f, 0.0f, 1.0f, 0.0f) * vmath::rotate(static_cast<gl::f32>(delta) * 81.0f, 1.0f, 0.0f, 0.0f);
        glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv_matrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    };
    virtual void shutdown() override {};

private:
    gl::Program program;
    gl::i32 mv_location;
    gl::i32 proj_location;
    gl::u32 buf;
    gl::f32 aspect_ratio;
    vmath::mat4 proj_matrix;
};
} // namespace dk

DECLARE_MAIN(dk::SpinningCubeApp);
