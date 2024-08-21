#include <dklib/math.h>
#include <dklib/dklib.h>

namespace dk {
class FirstTriangleApplication : public dk::gl::Application {
public:
    FirstTriangleApplication();
    virtual ~FirstTriangleApplication() = default;

    virtual void init() override {};
    virtual void startup() override {};
    virtual void render(double delta) override {
        // TODO: Create color type
        // TODO: Add common colors as static constants
        static const gl::f32 white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, white);
        program.use();
        // Sends Point primitive to pipeline
        glDrawArrays(GL_TRIANGLES, 0, 3);
    };
    virtual void shutdown() override {};

private:
    gl::Program program;
};
} // namespace dk
