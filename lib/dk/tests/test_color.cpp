#include <doctest/doctest.h>
#include <dklib/gl/color.hpp>

using namespace dk::gl;

TEST_SUITE("[Color] Color related tests") {
    TEST_CASE("it should be possible to initialize color") { Color(); }
    TEST_CASE("it should be possible to initialize color with default values") {
        auto color = Color();
        CHECK(color.get_red() == 0);
        CHECK(color.get_green() == 0);
        CHECK(color.get_blue() == 0);
        CHECK(color.get_alpha() == 0);
    }
    TEST_CASE("it should be possible to initialize color as RGB") {
        auto color = Color({ 1, 2, 3 });
        CHECK(color.get_red() == 1);
        CHECK(color.get_green() == 2);
        CHECK(color.get_blue() == 3);
        CHECK(color.get_alpha() == 0);
    }
    TEST_CASE("it should be possible to initialize color as RGBa") {
        auto color = Color({ 1, 2, 3, 4 });
        CHECK(color.get_red() == 1);
        CHECK(color.get_green() == 2);
        CHECK(color.get_blue() == 3);
        CHECK(color.get_alpha() == 4);
    }
    TEST_CASE("it should be possible to initialize colors individually as RGB") {
        Color color { 1, 2, 3 };
        CHECK(color.get_red() == 1);
        CHECK(color.get_green() == 2);
        CHECK(color.get_blue() == 3);
        CHECK(color.get_alpha() == 0);
    }
    TEST_CASE("it should be possible to initialize colors individually as RGBa") {
        Color color { 1, 2, 3, 4 };
        CHECK(color.get_red() == 1);
        CHECK(color.get_green() == 2);
        CHECK(color.get_blue() == 3);
        CHECK(color.get_alpha() == 4);
    }
    TEST_CASE("Color should have copy ctor") {
        Color color1 { 1, 2, 3, 4 };
        Color color2(color1);
        CHECK(color2.get_red() == 1);
        CHECK(color2.get_green() == 2);
        CHECK(color2.get_blue() == 3);
        CHECK(color2.get_alpha() == 4);
    }
    TEST_CASE("Color should have move ctor") {
        Color color1 { 1, 2, 3, 4 };
        Color color2(std::move(color1));
        CHECK(color2.get_red() == 1);
        CHECK(color2.get_green() == 2);
        CHECK(color2.get_blue() == 3);
        CHECK(color2.get_alpha() == 4);
    }
    TEST_CASE("Color should have copy assignement") {
        Color color1 { 1, 2, 3, 4 };
        Color color2 = color1;
        CHECK(color2.get_red() == 1);
        CHECK(color2.get_green() == 2);
        CHECK(color2.get_blue() == 3);
        CHECK(color2.get_alpha() == 4);
    }
    TEST_CASE("Color should have move assignement") {
        Color color1 { 1, 2, 3, 4 };
        Color color2 = std::move(color1);
        CHECK(color2.get_red() == 1);
        CHECK(color2.get_green() == 2);
        CHECK(color2.get_blue() == 3);
        CHECK(color2.get_alpha() == 4);
    }
}
