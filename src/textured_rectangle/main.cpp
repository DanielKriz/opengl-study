#include <GL/gl.h>
#include <GLES3/gl3.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <imgui.h>

#include <vector>

#include <dklib/dklib.h>

namespace dk {

class TexturedTriangleApplication : public sdl::Application {
public:
    TexturedTriangleApplication()
        : Application("Textured Rectangle")
        , program()
        , vbo()
        , ebo() {
        const std::string path_prefix = "src/textured_rectangle/";
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

        tex1_location = program.get_uniform("texture1");
        spdlog::info("First texture location {}", tex1_location);

        tex2_location = program.get_uniform("texture2");
        spdlog::info("second texture location {}", tex2_location);

        flag_location = program.get_uniform("is_blending_enabled");
        spdlog::info("flag location {}", flag_location);

        color_location = program.get_uniform("is_color_mode_enabled");
        spdlog::info("color location {}", color_location);

        blend_factor_location = program.get_uniform("blend_factor");
        spdlog::info("blend factor location {}", blend_factor_location);

        // TODO:
        // [ ] We need to specify some shape
        // [ ] Triangulate that shape (and provide indices)
        // [ ] Compute textire coordinates
        std::vector<gl::f32> vertices = {
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
           -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
           -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,
        };
        std::vector<gl::u8> indices = {
            0, 1, 3,
            1, 2, 3,
        };

        vbo.setup(vertices);
        ebo.setup(indices);

        // TODO: this should be done with some vertex structure
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(gl::f32), reinterpret_cast<void *>(0));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(gl::f32), reinterpret_cast<void *>(3 * sizeof(gl::f32)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(gl::f32), reinterpret_cast<void *>(6 * sizeof(gl::f32)));
        glEnableVertexAttribArray(2);

        // TODO: ^^^ Both the vertex structure and buffers should be contained
        // in some kind of Drawable.
        // We should be able to say whether we should provide:
        // 1. Vertices
        // 2. Colors
        // 3. Texturing coordinates

        // TODO: it should be possible to bind some texture to this drawable
        // and throw an exception (or something similar) if the drawable does
        // not allow texturing.


        gl::u32 current_tex;
        // Wall texture
        spdlog::info("Loading the first texture");
        glGenTextures(1, &current_tex);
        spdlog::info("Descriptor of first texture {}" , current_tex);
        glBindTexture(GL_TEXTURE_2D, current_tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // TODO: this whole loading process should be contained somewhere and
        // surface should serve as some kind of container. (perhaps we could
        // use std::span for that).
        SDL_Surface *tex_surface = IMG_Load("src/textured_rectangle/wall.jpg");
        if (tex_surface == nullptr) {
            throw std::runtime_error("Could not load texture");
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_surface->w, tex_surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_surface->pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
        SDL_FreeSurface(tex_surface);
        tex_surface = nullptr;
        textures.push_back(current_tex);

        // Container texture
        spdlog::info("Loading the second texture");
        glGenTextures(1, &current_tex);
        spdlog::info("Descriptor of second texture {}" , current_tex);
        glBindTexture(GL_TEXTURE_2D, current_tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        tex_surface = IMG_Load("src/textured_rectangle/container.jpg");
        if (tex_surface == nullptr) {
            throw std::runtime_error("Could not load texture");
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_surface->w, tex_surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_surface->pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
        SDL_FreeSurface(tex_surface);
        tex_surface = nullptr;
        textures.push_back(current_tex);

        // Happy face texture
        spdlog::info("Loading the third texture");
        glGenTextures(1, &current_tex);
        spdlog::info("Descriptor of third texture {}" , current_tex);
        glBindTexture(GL_TEXTURE_2D, current_tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // TODO: this image needs to be flipped, thus we should be able to do
        // so with some method of Image class.
        tex_surface = IMG_Load("src/textured_rectangle/awesomeface.png");
        spdlog::info("count of bytes in face texture: {}", tex_surface->format->BytesPerPixel);
        if (tex_surface == nullptr) {
            throw std::runtime_error("Could not load texture");
        }
        // NOTE: mind the RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_surface->w, tex_surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_surface->pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
        SDL_FreeSurface(tex_surface);
        tex_surface = nullptr;
        textures.push_back(current_tex);


        register_callback(SDL_KEYUP, [this](const SDL_Event &event) {
            auto &key_pressed = event.key.keysym.sym;
            if (key_pressed == SDLK_SPACE) {
                spdlog::info("Different texture mode");
                is_blending_enabled = not is_blending_enabled;
            } else if (key_pressed == SDLK_c) {
                is_color_mode_enabled = not is_color_mode_enabled;
                spdlog::info("Color mode");
            } else if (key_pressed == SDLK_UP) {
                ++active_texture;
                active_texture %= textures.size();
            } else if (key_pressed == SDLK_DOWN) {
                active_texture = active_texture == 0 ? textures.size() - 1 : active_texture - 1;
            }
        });

        active_texture = *textures.begin();
    }

    virtual ~TexturedTriangleApplication() {};

    virtual void render(double delta) override {
        glViewport(0, 0, info.window_width, info.window_height);
        gl::clear_buffers(gl::BufferType::COLOR | gl::BufferType::DEPTH);

        // TODO: We have to think about the number of texturing units for
        // a single drawable object and how to contain such thing.
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[active_texture]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures[(active_texture + 1) % textures.size()]);

        program.use();
        // NOTE: uniforms have to be set in the game loop, otherwise it won't
        // work.
        glUniform1i(tex1_location, 0);
        glUniform1i(tex2_location, 1);

        // TODO: provide syntactical sugar for methods with booleans.
        glUniform1i(flag_location, is_blending_enabled);
        glUniform1i(color_location, is_color_mode_enabled);
        glUniform1f(blend_factor_location, blend_factor);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);

        // TODO: We should probably add some method solely used for GUI rendering,
        // it can be here, but I think that it only clutters the important
        // rendering code.
        ImGui::Begin("Help");
        ImGui::Text("space - changing the application mode");
        ImGui::Text("c - enabling color mode");
        ImGui::Text("up and down - cycling between textures");
        ImGui::SliderFloat("Blend Factor", &blend_factor, 0.0f, 1.0f);
        ImGui::End();
    }

private:
    gl::f32 blend_factor { 0.2 };

    // TODO: get rid of these thanks to the new Uniform class
    gl::i32 tex1_location;
    gl::i32 tex2_location;
    gl::i32 flag_location;
    gl::i32 color_location;
    gl::i32 blend_factor_location;

    bool is_blending_enabled {true};
    bool is_color_mode_enabled {true};
    gl::Program program;
    gl::VertexBuffer vbo;
    gl::ElementBuffer ebo;
    gl::u32 active_texture;
    std::vector<gl::u32> textures;
};
} // namespace dk

DECLARE_MAIN(dk::TexturedTriangleApplication);
