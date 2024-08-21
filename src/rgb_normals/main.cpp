#include <GL/gl.h>

#include <dklib/file.h>
#include <dklib/dklib.h>

#include <imgui.h>

#include <string_view>
#include <vector>

namespace dk {
class MeshWithIndicesApplication : public sdl::Application {
public:
    MeshWithIndicesApplication()
        : Application("Mesh rendering with indices")
        , program()
        , aspect_ratio(static_cast<gl::f32>(info.window_width) / static_cast<gl::f32>(info.window_height)) {
        const std::string path_prefix = "src/rgb_normals/";
        program
            .attach_shader(path_prefix + "main.frag.glsl", gl::ShaderType::FRAGMENT)
            .attach_shader(path_prefix + "main.vert.glsl", gl::ShaderType::VERTEX)
            .link();

        // Informations about uniforms, etc.
        {
            gl::i32 size;
            gl::size len;
            gl::enum32 type;
            char name[256];
            gl::i32 cnt;
            glGetProgramiv(program.get_id(), GL_ACTIVE_UNIFORMS, &cnt);
            for (int i = 0; i < cnt; ++i) {
                glGetActiveUniform(program.get_id(), i, 256, &len, &size, &type, name);
                std::string_view str_container { name };
                spdlog::info("Uniform #{} Type: {} Name '{}'", i, type, str_container);
            }
            glGetProgramiv(program.get_id(), GL_ACTIVE_ATTRIBUTES, &cnt);
            for (int i = 0; i < cnt; ++i) {
                glGetActiveAttrib(program.get_id(), i, 256, &len, &size, &type, name);
                std::string_view str_container { name };
                spdlog::info("Attribute #{} Type: {} Name '{}'", i, type, str_container);
            }
        }

        meshes.reserve(4);
        meshes.emplace_back(
            dk::file::obj::experimental::read<dk::gl::experimental::Vertex>(
                "assets/obj_files/cube.obj"
            )
        );
        meshes.emplace_back(
            dk::file::obj::experimental::read<dk::gl::experimental::Vertex>(
                "assets/obj_files/cone.obj"
            )
        );
        meshes.emplace_back(
            dk::file::obj::experimental::read<dk::gl::experimental::Vertex>(
                "assets/obj_files/monkey.obj"
            )
        );
        meshes.emplace_back(
            dk::file::obj::experimental::read<dk::gl::experimental::Vertex>(
                "assets/obj_files/bunny_v2.obj"
            )
        );

        mv_location = program.get_uniform("mv_matrix");
        proj_location = program.get_uniform("proj_matrix");
        scale_location = program.get_uniform("scale_matrix");

        program.get_uniform(true, "mv_matrix");

        proj_matrix = vmath::perspective(50.0f, aspect_ratio, 0.1f, 1000.0f);

        // TODO indeces => indices

        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        spdlog::info("registering callback");

        // TODO: this is so common that I should add it to base class
        register_callback(SDL_WINDOWEVENT, [this](const SDL_Event &event) {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                info.window_width = event.window.data1;
                info.window_height = event.window.data2;
                aspect_ratio = static_cast<gl::f32>(info.window_width) / static_cast<gl::f32>(info.window_height);
                proj_matrix = vmath::perspective(50.0f, aspect_ratio, 0.1f, 1000.0f);
            }
        });
        register_callback(SDL_KEYUP, [this](const SDL_Event &event) {
            auto &key_pressed = event.key.keysym.sym;
            if (key_pressed == SDLK_SPACE) {
                ++drawed_shape;
                drawed_shape %= meshes.size();
                spdlog::info("current draw shape ID: {}", drawed_shape);
            } else if (key_pressed == SDLK_UP) {
                ++mesh_cnt;
                spdlog::info("current mesh count: {}", mesh_cnt);
            } else if (key_pressed == SDLK_DOWN) {
                mesh_cnt = mesh_cnt == 0 ? mesh_cnt : --mesh_cnt;
                spdlog::info("current mesh count: {}", mesh_cnt);
            }
        });
    }

    virtual ~MeshWithIndicesApplication() {};

    virtual void render(double delta) override {
        glViewport(0, 0, info.window_width, info.window_height);
        gl::clear_buffers(gl::BufferType::COLOR | gl::BufferType::DEPTH);

        program.use();

        ImGui::Begin("Scale and stride options");
        ImGui::SliderFloat("Scale factor", &SCALE_FACTOR, 0.0f, 1.0f);
        ImGui::SliderFloat("Stride factor", &STRIDE_FACTOR, 0.0f, 100.0f);
        ImGui::SliderInt("Mesh count", &mesh_cnt, 0, 255);
        ImGui::Checkbox("Enable rotation", &is_rotation_enabled);
        ImGui::End();

        glUniformMatrix4fv(proj_location, 1, GL_FALSE, proj_matrix);

        scale_matrix = vmath::scale(SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR);
        glUniformMatrix4fv(scale_location, 1, GL_FALSE, scale_matrix);

        for (gl::i32 i = 0; i < mesh_cnt; ++i) {
            gl::f32 stride = i == 1 ? 1.0f : static_cast<gl::f32>(i) * STRIDE_FACTOR;
            gl::f32 f = stride * static_cast<gl::f32>(delta) * 0.3f;
            if (is_rotation_enabled) {
                mv_matrix = vmath::translate(0.0f, 0.0f, -4.0f) * vmath::translate(sinf(2.1f * f) * 0.5f, cosf(1.7f * f) * 0.5f, sinf(1.3f * f) * cosf(1.5f * f) * 2.0f) * vmath::rotate(static_cast<gl::f32>(delta) * 45.0f, 0.0f, 1.0f, 0.0f) * vmath::rotate(static_cast<gl::f32>(delta) * 81.0f, 1.0f, 0.0f, 0.0f);
            }
            glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv_matrix);

            meshes[drawed_shape % meshes.size()].draw();
        }
    }

private:
    gl::f32 STRIDE_FACTOR = 1.0f;
    gl::f32 SCALE_FACTOR = 1.0f;
    gl::Program program;
    gl::i32 mv_location;
    gl::i32 proj_location;
    gl::i32 scale_location;
    gl::f32 aspect_ratio;
    vmath::mat4 proj_matrix;
    vmath::mat4 scale_matrix;
    vmath::mat4 mv_matrix;
    // std::vector<gl::TriangularMesh> meshes;
    std::vector<gl::Mesh<gl::experimental::Vertex>> meshes;
    gl::u8 drawed_shape { 0 };
    gl::i32 mesh_cnt { 1 };
    bool is_rotation_enabled { true };
};
} // namespace dk

DECLARE_MAIN(dk::MeshWithIndicesApplication);
