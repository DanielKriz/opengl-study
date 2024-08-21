
#include <GL/gl.h>
#include <GLES3/gl3.h>
#include <imgui.h>
#include <spdlog/spdlog.h>

#include <dklib/dklib.h>

#include <array>
#include <type_traits>

using namespace dk::gl;

namespace dk {

struct TriangleVertex {
    math::Vector3D position;
    math::Vector3D color;
};

class ColoredScreen : public sdl::Application {
public:
    ColoredScreen()
        : Application("Colored Scrren") {
        const std::string path_prefix = "src/test_colored_screen/";
        program
            .attach_shader(path_prefix + "main.frag.glsl", gl::ShaderType::FRAGMENT)
            .attach_shader(path_prefix + "main.vert.glsl", gl::ShaderType::VERTEX)
            .link();

        float vertices[] = {
            -0.5f,
            -0.5f,
            0.0f,
            1.0f,
            0.0f,
            0.0f,
            0.5f,
            -0.5f,
            0.0f,
            0.0f,
            1.0f,
            0.0f,
            0.0f,
            0.5f,
            0.0f,
            0.0f,
            0.0f,
            1.0f,
        };

        static_assert(std::is_standard_layout_v<math::Vector3D>);

        std::array<TriangleVertex, 3> triangle = { {
            { math::Vector3D { -0.5f, -0.5f, 0.0f }, math::Vector3D { 1.0f, 0.0f, 0.0f } },
            { math::Vector3D { 0.5f, -0.5f, 0.0f }, math::Vector3D { 0.0f, 1.0f, 0.0f } },
            { math::Vector3D { 0.0f, 0.5f, 0.0f }, math::Vector3D { 0.0f, 0.0f, 1.0f } },
        } };

        auto size = sizeof(TriangleVertex);
        auto arr_size = sizeof(triangle);
        spdlog::info("Size of vertex: {}", size);
        spdlog::info("Size of Array: {}", arr_size);
        spdlog::info("Size of alt Array: {}", 6 * triangle.size() * sizeof(f32));
        spdlog::info("size of vertices: {}", sizeof(vertices));

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        // glBufferData(GL_ARRAY_BUFFER, size, triangle.data(), GL_STATIC_DRAW);
        glBufferData(GL_ARRAY_BUFFER, 6 * triangle.size() * sizeof(f32), triangle.data(), GL_STATIC_DRAW);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
        // GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(f32), reinterpret_cast<void *>(0));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(f32), reinterpret_cast<void *>(3 * sizeof(f32)));
        glEnableVertexAttribArray(1);
    }

    virtual ~ColoredScreen() {};

    virtual void render(double delta) override {

        static const gl::f32 white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, white);
        program.use();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

private:
    gl::Program program;
    u32 vbo;
};
} // namespace dk

DECLARE_MAIN(dk::ColoredScreen);
