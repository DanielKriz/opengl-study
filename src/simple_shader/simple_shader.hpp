#include <GL/gl.h>
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

#include <dklib/dklib.h>

#include <cmath>
#include <fstream>

namespace dk {
class SimpleShaderApplication : public dk::gl::Application {
public:
    SimpleShaderApplication();
    virtual ~SimpleShaderApplication() = default;
    virtual void init() override {};
    virtual void startup() override {};
    virtual void render(double delta) override {
        const gl::f32 color[] = { static_cast<float>(sin(delta) * 0.5f + 0.5f),
                                  static_cast<float>(cos(delta) * 0.5f + 0.5f), 0.0f,
                                  1.0f };
        glClearBufferfv(GL_COLOR, 0, color);
        prog.use();
        // TODO: add this to the gl library

        // Sets size of a point to 40px
        glPointSize(40.0f);
        // Sends Point primitive to pipeline
        glDrawArrays(GL_POINTS, 0, 1);
    };
    virtual void shutdown() override {};

private:
    gl::Program prog;
};
} // namespace dk
