#include <GL/gl.h>
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <filesystem>

#include <dklib/dklib.h>
#include <spdlog/spdlog.h>

namespace dk {
class TessellatedTriangleApplication : public dk::gl::Application {
public:
    TessellatedTriangleApplication();
    virtual ~TessellatedTriangleApplication();

    virtual void init() override {};
    virtual void startup() override {};
    virtual void render(double delta) override {
        const gl::f32 color[] = { static_cast<gl::f32>(sin(delta) * 0.5f + 0.5f),
                                  static_cast<gl::f32>(cos(delta) * 0.5f + 0.5f),
                                  0.0f, 1.0f };
        gl::ColorBuffer::clear(0, color);
        // glClearBufferfv(GL_COLOR, 0, color);

        program.use();

        gl::f32 attributes[] = { static_cast<gl::f32>(sin(delta) * 0.5f),
                                 static_cast<gl::f32>(cos(delta) * 0.6f), 0.0f,
                                 0.0f };

        glVertexAttrib4fv(0, attributes);
        // Sends Point primitive to pipeline
        // gl::draw(gl::DrawMode::TRIANGLES, 0, 3);
        glDrawArrays(GL_PATCHES, 0, 3);
    };
    virtual void shutdown() override {};

private:
    gl::Program program;
    gl::u32 vao;
};
} // namespace dk
