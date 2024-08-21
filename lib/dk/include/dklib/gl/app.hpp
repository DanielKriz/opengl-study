#ifndef DK_OPENGL_APP_HPP
#define DK_OPENGL_APP_HPP

#include <GLFW/glfw3.h>
#include <SDL2/SDL.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl2.h>
#include <spdlog/spdlog.h>

#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

#include "gltypes.hpp"

// TODO: move somewhere else
namespace dk {
enum class KeyCode {};
enum class MouseButton {};
enum class Action {};

struct Position {
    std::size_t x { 0 };
    std::size_t y { 0 };
};
} // namespace dk

namespace dk::gl {
class Application {
public:
    Application(std::string &&title = "");
    virtual ~Application();
    virtual void run(Application &app);
    // NOTE: this sounds just like a two-step ctor...
    virtual void init() = 0;
    virtual void startup() = 0;
    virtual void render(double delta) = 0;
    // NOTE: this sounds just like a dtor...
    virtual void shutdown() = 0;
    virtual void set_window_title(std::string &title);

    dk::Position get_mouse_position();

    /// Callbacks
    virtual void on_resize(GLFWwindow *win, int width, int height) {};
    virtual void on_key(GLFWwindow *win, int key_code, int action) {};
    virtual void on_mouse_button(GLFWwindow *win, int button, int action) {};

    virtual void on_resize(int width, int height) {
        on_resize(window.get(), width, height);
    }
    virtual void on_key(dk::KeyCode key_code, dk::Action action) {
        on_key(window.get(), static_cast<int>(key_code), static_cast<int>(action));
    }

    virtual void on_mouse_button(dk::MouseButton button, dk::Action action) {
        on_mouse_button(window.get(), static_cast<int>(button), static_cast<int>(action));
    }
    // NOTE: in the book they are proposing a mouse wheel action, but mouse
    // wheel is just a third button on mouse, or is it not?

    // TODO: add some kind of support for debugging, perhaps some stream or
    // function that I have to initialize (it may wrap stream or fmt library)
    struct Info {
        std::string title { "OpenGL Window" };
        int window_width { 800 };
        int window_height { 600 };
        int sample_count { 30 };
        struct flags {
            unsigned int fullscreen : 1 { 0 };
            unsigned int vsync : 1 { 0 };
            unsigned int cursor : 1 { 1 };
            unsigned int stereo : 1 { 0 };
            unsigned int debug : 1 { 1 };
            unsigned int robust : 1 { 0 };
        };
        flags flags {};
    };
    Info info {};

    void set_fullscreen(bool enable) { info.flags.fullscreen = enable ? 1 : 0; };
    void set_vsync(bool enable) { info.flags.vsync = enable ? 1 : 0; };
    void set_cursor(bool enable) { info.flags.cursor = enable ? 1 : 0; };
    void set_stereo(bool enable) { info.flags.stereo = enable ? 1 : 0; };
    void set_debug(bool enable) { info.flags.debug = enable ? 1 : 0; };
    void set_robust(bool enable) { info.flags.robust = enable ? 1 : 0; };

protected:
    using WindowDeleter = std::function<void(GLFWwindow *)>;
    std::unique_ptr<GLFWwindow, WindowDeleter> window;
};
}; // namespace dk::gl

namespace dk::sdl {
/// @brief Callback typedef used withing SDL event handling system
using EventCallback = std::function<void(SDL_Event const &)>;

/// @brief SDL specific application with ImGUI support
///
/// This class encloses the application context together with main render
/// and event handling loop.
class Application {
public:
    /// @brief application constructor
    ///
    /// @param title is a title of the window, that is to be shown in the
    /// title bar
    Application(std::string &&title = "");
    virtual ~Application();

    /// @brief internal structure that holds information about application
    struct {
        /// Title of a window
        std::string title { "OpenGL Window" };
        /// Width of the window in pixel
        unsigned int window_width { 800 };
        /// Height of the window in pixel
        unsigned int window_height { 600 };
        /// Number of frames per second
        unsigned int sample_count { 30 };
        /// Various flags application flags
        struct {
            unsigned int fullscreen : 1 { 0 };
            unsigned int vsync : 1 { 0 };
            unsigned int cursor : 1 { 1 };
            unsigned int stereo : 1 { 0 };
            unsigned int debug : 1 { 1 };
            unsigned int robust : 1 { 0 };
        } flags {};
        // flags flags {};
    } info {};

    /// @brief Main application runtime loop
    // TODO: remove that weak approach to polymorphism
    virtual void run(Application &app);

    /// @brief Pure virtual rendering routine.
    ///
    /// Each child application is supposed to define its own rendering. But
    /// the application loop is enclosed in the run function.
    virtual void render(double current_time) = 0;

    virtual void render_gui() {};

    /// @brief Event handling routine
    ///
    /// Processed event are propagated to the ImGUI too.
    virtual void handle_events();

    /// @brief Registration of new SDL callbacks.
    ///
    /// It is possible to have multiple callbacks registered for single
    /// event type.
    ///
    /// @param type an SDL event type for which we are going to register
    ///        the callback.
    /// @param callback callback function
    virtual void register_callback(SDL_EventType type, const EventCallback &callback);

private:
    /// Function object for the SDL window deleter
    using WindowDeleter = std::function<void(SDL_Window *)>;
    /// A pointer to SDL window with deleter function
    std::unique_ptr<SDL_Window, WindowDeleter> window;
    /// Mandatory OpenGL context required for OpenGL rendering inside of SDL
    SDL_GLContext context;
    /// Map of watched event types and their callbacks
    std::map<SDL_EventType, std::vector<EventCallback>> registered_callbacks_;
    /// Identifies whether application is still running
    bool running_ { true };
};
} // namespace dk::sdl

#endif // DK_OPENGL_APP_HPP
