#ifndef DK_SDL_EXCEPTION_HPP
#define DK_SDL_EXCEPTION_HPP

#include <SDL2/SDL.h>
#include <fmt/core.h>
#include <stdexcept>

namespace dk::sdl {
class runtime_error : public std::runtime_error {
public:
    runtime_error(std::string &&function_name)
        : std::runtime_error(create_error_msg(function_name)) {};
    runtime_error(std::string &function_name);
    runtime_error(runtime_error &other);

    virtual ~runtime_error() noexcept = default;

private:
    std::string create_error_msg(std::string &function_name);
};
} // namespace dk::sdl

#endif // DK_SDL_EXCEPTION_HPP
