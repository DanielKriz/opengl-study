#include <dklib/sdl/exception.hpp>

namespace dk::sdl {
std::string runtime_error::create_error_msg(std::string &function_name) {
    return fmt::format("{} failed with: {}\n", function_name, SDL_GetError());
}
} // namespace dk::sdl
