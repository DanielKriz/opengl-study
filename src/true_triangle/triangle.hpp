#include <GL/gl.h>
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <filesystem>

#include <dklib/dklib.h>
#include <spdlog/spdlog.h>

namespace dk {
class TrueTriangleApplication : public dk::gl::Application {
public:
    TrueTriangleApplication();
    virtual ~TrueTriangleApplication();

    virtual void init() override {};
    virtual void startup() override {};
    virtual void render(double delta) override {
        const gl::f32 black[] = { 0.0f, 0.0, 0.0f, 1.0f };
        gl::ColorBuffer::clear(0, black);

        program.use();

        gl::draw(gl::DrawMode::TRIANGLES, 0, 3);
    };
    virtual void shutdown() override {};

private:
    gl::Program program;
};
} // namespace dk
