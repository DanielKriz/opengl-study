#include <dklib/gl/app.hpp>

namespace dk::gl {
Application::Application(std::string &&title) {
    if (not glfwInit()) {
        throw std::runtime_error("Could not initialize GLFW");
    }

    if (title != "") {
        info.title = title;
    }

    // This all is just window initilization
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    if (info.flags.debug) {
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    }
    if (info.flags.robust) {
        glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_LOSE_CONTEXT_ON_RESET);
    }
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, info.sample_count);
    glfwWindowHint(GLFW_STEREO, info.flags.stereo ? GL_TRUE : GL_FALSE);

    window = std::unique_ptr<GLFWwindow, WindowDeleter>(
        glfwCreateWindow(
            info.window_width, info.window_height, info.title.c_str(),
            info.flags.fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr
        ),
        [](GLFWwindow *win_ptr) { glfwDestroyWindow(win_ptr); }
    );
    if (not window.get()) {
        throw std::runtime_error("Could not create GLFW window");
    }

    glfwMakeContextCurrent(window.get());

    // TODO: resolve the callbacks somehow
    // glfwSetWindowSizeCallback(window.get(), &Application::on_resize);
    // create_glfw_adapters(window.get(), this);

    if (not info.flags.cursor) {
        glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }
}

Application::~Application() { glfwTerminate(); }

void Application::run(Application &app) {
    spdlog::info("Starting the application");
    bool running = true;

    // FIXME: I get no information from these
    // spdlog::info("Vendor: {}", (char *)glGetString(GL_VENDOR));
    // spdlog::info("Version: {}", (char *)glGetString(GL_VERSION));
    // spdlog::info("Renderer: {}", (char *)glGetString(GL_RENDERER));

    do {
        render(glfwGetTime());

        glfwSwapBuffers(window.get());
        glfwPollEvents();

        running &= (glfwGetKey(window.get(), GLFW_KEY_ESCAPE) == GLFW_RELEASE);
        running &= (glfwWindowShouldClose(window.get()) != GL_TRUE);
    } while (running);

    // glfwTerminate();
    spdlog::info("Ending the application");
}

void Application::set_window_title(std::string &title) { }

dk::Position Application::get_mouse_position() { return { 0, 0 }; }
} // namespace dk::gl

namespace dk::sdl {
Application::Application(std::string &&title) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Could not initialize SDL");
    }

    if (title.empty()) {
        title = info.title;
    }

    // auto video_information = SDL_GetVideoInfo();

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    window = std::unique_ptr<SDL_Window, WindowDeleter>(
        SDL_CreateWindow(
            title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            info.window_width, info.window_height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
        ),
        [](SDL_Window *win_ptr) { SDL_DestroyWindow(win_ptr); }
    );

    context = SDL_GL_CreateContext(window.get());

    SDL_GL_SetSwapInterval(1);

    // Setting up Event handler
    register_callback(SDL_KEYDOWN, [this](SDL_Event const &event) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            running_ = false;
        }
    });
    register_callback(SDL_QUIT, [this](SDL_Event const &event) { running_ = false; });

    // Setting up ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplSDL2_InitForOpenGL(window.get(), context);
    ImGui_ImplOpenGL3_Init();
}

Application::~Application() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(context);
    SDL_Quit();
}

void Application::register_callback(SDL_EventType type, const EventCallback &callback) {
    registered_callbacks_[type].push_back(callback);
}

void Application::handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        ImGui_ImplSDL2_ProcessEvent(&event);
        for (auto &callback :
             registered_callbacks_[static_cast<SDL_EventType>(event.type)]) {
            callback(event);
        }
    }
}

void Application::run(Application &app) {
    spdlog::info("Starting the application");
    bool running = true;
    do {
        handle_events();
        /* SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_WINDOWEVENT:
                switch (event.window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                    spdlog::info("resized to {}x{}", event.window.data1,
        event.window.data2); break;
                }
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    running = false;
                    break;
                case SDLK_SPACE:
                    spdlog::info("Space pressed");
                    break;
                }
                break;
            }
        } */
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        // ImGui::ShowDemoWindow();

        render(static_cast<dk::gl::f64>(SDL_GetTicks()) / 1000);
        render_gui();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(window.get());
    } while (running_);
    spdlog::info("Ending the application");
}
} // namespace dk::sdl
