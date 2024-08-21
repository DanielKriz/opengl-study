#ifndef DK_SDL_WINDOW_HPP
#define DK_SDL_WINDOW_HPP

#include "context.hpp"
#include <SDL2/SDL.h>

namespace dk::sdl {
class Window {
public:
    void assign_context(Context ctx);

private:
};
} // namespace dk::sdl
#endif // DK_SDL_WINDOW_HPP
