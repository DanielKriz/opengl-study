#include <dklib/sdl/runtime.hpp>

namespace dk::sdl {
// We want to check that our wrapper is indeed compatible
namespace {
    using T = decltype(SDL_INIT_EVERYTHING);
    static_assert(static_cast<T>(InitFlags::timer) == SDL_INIT_TIMER);
    static_assert(static_cast<T>(InitFlags::audio) == SDL_INIT_AUDIO);
    static_assert(static_cast<T>(InitFlags::video) == SDL_INIT_VIDEO);
    static_assert(static_cast<T>(InitFlags::joystick) == SDL_INIT_JOYSTICK);
    static_assert(static_cast<T>(InitFlags::haptic) == SDL_INIT_HAPTIC);
    static_assert(static_cast<T>(InitFlags::game_controller) == SDL_INIT_GAMECONTROLLER);
    static_assert(static_cast<T>(InitFlags::events) == SDL_INIT_EVENTS);
    static_assert(static_cast<T>(InitFlags::everything) == SDL_INIT_EVERYTHING);
    static_assert(static_cast<T>(InitFlags::no_parachute) == SDL_INIT_NOPARACHUTE);
} // namespace

Runtime::Runtime(InitFlags flags) {
    spdlog::info("Creating an instance of SDL Runtime");
    SDL_InitSubSystem(static_cast<unsigned>(flags));
};

void Runtime::init(InitFlags flags) {
    if (not Runtime::is_initalized()) {
        SDL_InitSubSystem(static_cast<unsigned>(flags));
    }
}

const Runtime &Runtime::get_instance() {
    if (instance == nullptr) {
        // instance = std::make_unique<Runtime>();
        // instance.reset(new Runtime);
    }
    return *instance;
}
} // namespace dk::sdl
