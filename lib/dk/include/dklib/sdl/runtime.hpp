#ifndef DK_SDL_RUNTIME_HPP
#define DK_SDL_RUNTIME_HPP

#include <memory>

#include <SDL2/SDL.h>
#include <spdlog/spdlog.h>

namespace dk::sdl {
/// Wrapper around SDL initialization flags.
enum class InitFlags {
    /// Inits the timer subsystem.
    timer = SDL_INIT_TIMER,
    /// Inits the audio subsystem.
    audio = SDL_INIT_AUDIO,
    /// Inits the video subsystem.
    video = SDL_INIT_VIDEO,
    /// Inits the joystick subsystem.
    joystick = SDL_INIT_JOYSTICK,
    /// Inits the haptic subsystem.
    haptic = SDL_INIT_HAPTIC,
    /// Inits the game controller subsystem.
    game_controller = SDL_INIT_GAMECONTROLLER,
    /// Inits the events subsystem.
    events = SDL_INIT_EVENTS,
    /// Inits the every subsystem.
    everything = SDL_INIT_EVERYTHING,
    /// This is is only kept for compatibility reasons with SDL1.
    no_parachute = SDL_INIT_NOPARACHUTE,
};
// These have to be defined here, because they are inlined
/// Or operator which enables us to scoped enum wrapper like the old enums.
inline InitFlags operator|(InitFlags lhs, InitFlags rhs) {
    using T = std::underlying_type_t<InitFlags>;
    return static_cast<InitFlags>(static_cast<T>(lhs) | static_cast<T>(rhs));
}
inline InitFlags &operator|=(InitFlags &lhs, InitFlags rhs) {
    lhs = lhs | rhs;
    return lhs;
}

/// @brief SDL runtime that simulates call of the SDL_Init() function
///
/// It is a singleton for which each class checks whether it was already
/// created.
class Runtime {
public:
    static bool is_initalized();
    static void init(InitFlags flags);
    static const Runtime &get_instance();
    ~Runtime();

    Runtime(const Runtime &) = delete;
    void operator=(const Runtime &) = delete;

private:
    Runtime(InitFlags flags);
    static std::unique_ptr<Runtime> instance;
    static bool initialzed_;
    static InitFlags flags;
};
} // namespace dk::sdl
#endif // DK_SDL_RUNTIME_HPP
