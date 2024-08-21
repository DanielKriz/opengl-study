#include <doctest/doctest.h>
#include <dklib/sdl/runtime.hpp>

#include <bitset>
#include <iostream>
#include <map>

using namespace dk;

const std::vector<sdl::InitFlags> flags {
    sdl::InitFlags::timer,
    sdl::InitFlags::audio,
    sdl::InitFlags::video,
    sdl::InitFlags::joystick,
    sdl::InitFlags::haptic,
    sdl::InitFlags::game_controller,
    sdl::InitFlags::events,
    sdl::InitFlags::everything,
    sdl::InitFlags::no_parachute,
};

using INIT_T = decltype(SDL_INIT_VIDEO);

std::map<sdl::InitFlags, INIT_T> flag_map {
    { sdl::InitFlags::timer, SDL_INIT_TIMER },
    { sdl::InitFlags::audio, SDL_INIT_AUDIO },
    { sdl::InitFlags::video, SDL_INIT_VIDEO },
    { sdl::InitFlags::joystick, SDL_INIT_JOYSTICK },
    { sdl::InitFlags::haptic, SDL_INIT_HAPTIC },
    { sdl::InitFlags::game_controller, SDL_INIT_GAMECONTROLLER },
    { sdl::InitFlags::events, SDL_INIT_EVENTS },
    { sdl::InitFlags::everything, SDL_INIT_EVERYTHING },
    { sdl::InitFlags::no_parachute, SDL_INIT_NOPARACHUTE },
};

TEST_SUITE("SDL Runtime") {
    TEST_CASE("It should be possible to use | operator on flags") {
        for (const auto flag1 : flags) {
            CAPTURE(flag1);
            for (const auto flag2 : flags) {
                CAPTURE(flag2);
                CHECK(static_cast<INIT_T>(flag1 | flag2) == (flag_map[flag1] | flag_map[flag2]));
            }
        }
    }
}
