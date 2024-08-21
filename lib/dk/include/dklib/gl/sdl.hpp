#ifndef DK_SDL_HPP
#define DK_SDL_HPP

#include <SDL.h>
#include <SDL_image.h>

#include <dklib/gl/color.hpp>
#include <dklib/gl/gltypes.hpp>

class Rectangle;

namespace dk::sdl {
enum class EventType {

};

class SDLObject {
public:
    SDLObject();

private:
    static bool is_initialized;
};

class Window {
public:
private:
};

class Renderer {
public:
private:
};

class Surface {
public:
    Surface();
    ~Surface();

    SDL_Surface *ptr();
    void fill_with_color(gl::Color color);

    [[nodiscard]] gl::u32 width() const noexcept;
    [[nodiscard]] gl::u32 height() const noexcept;

    [[nodiscard]] gl::u32 width_squared() const noexcept;
    [[nodiscard]] gl::u32 height_squared() const noexcept;

    void set_clip_region(gl::i32 x, gl::i32 y);
    void set_clip(Rectangle rect);

    void reset_clip_region();
    Rectangle get_clip_region();

private:
    SDL_Surface *surface_ptr_;
    bool has_texture_;
    gl::u32 texture_descriptor_;
};

using IImage = Surface;

class Image : public SDLObject {
public:
    Image();
    ~Image() { SDL_FreeSurface(surface_ptr); }

private:
    SDL_Surface *surface_ptr;
};

} // namespace dk::sdl

#endif // DK_SDL_HPP
