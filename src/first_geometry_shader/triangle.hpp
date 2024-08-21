#include <GL/gl.h>
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <filesystem>

#include <dklib/dklib.h>
#include <spdlog/spdlog.h>

namespace dk {
class GeometryApplication : public dk::gl::Application {
public:
    GeometryApplication();
    virtual ~GeometryApplication();

    virtual void init() override {};
    virtual void startup() override {};
    virtual void render(double delta) override {
        const gl::f32 color[] { 0.0f, 0.25f, 0.0f, 1.0f };
        gl::ColorBuffer::clear(0, color);

        program.use();

        glPointSize(5.0f);
        glDrawArrays(GL_PATCHES, 0, 3);
    };
    virtual void shutdown() override {};

private:
    gl::Program program;
    gl::u32 vao;
};
} // namespace dk
