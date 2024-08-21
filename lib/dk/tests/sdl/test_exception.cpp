#include <SDL2/SDL.h>
#include <doctest/doctest.h>
#include <iostream>

#include <dklib/sdl/exception.hpp>

using namespace dk;

TEST_SUITE("SDL Exception") {
    TEST_CASE("exception should throw") {
        try {
            SDL_SetError("Testing Error");
            throw sdl::runtime_error("SDL_Init");
        } catch (sdl::runtime_error &e) {
            std::cout << e.what() << std::endl;
            SDL_Quit();
        }
    }
}
