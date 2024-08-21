#include <GL/gl.h>
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

#include <dklib/dklib.h>

namespace dk {
class HelloWorldApplication : public dk::gl::Application {
public:
    HelloWorldApplication();
    virtual ~HelloWorldApplication() = default;
    virtual void init() override {};
    virtual void startup() override {};
    virtual void render([[maybe_unused]] double delta) override {
        static const gl::f32 red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, red);
    };
    virtual void shutdown() override {};

private:
    gl::Program prog;
};
} // namespace dk
