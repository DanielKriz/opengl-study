#include <doctest/doctest.h>

#include <dklib/util.h>

using namespace dk;

TEST_SUITE_BEGIN("String Util");

TEST_CASE("Split string by space") {
    const std::string got = "Hello World Here";
    auto res = util::split_by_delimeter(got, " ");
    CHECK(res.size() == 3);
    CHECK(res[0] == "Hello");
    CHECK(res[1] == "World");
    CHECK(res[2] == "Here");
}

TEST_CASE("Split string by word") {
    const std::string got = "Hello World Here";
    auto res = util::split_by_delimeter(got, " World ");
    CHECK(res.size() == 2);
    CHECK(res[0] == "Hello");
    CHECK(res[1] == "Here");
}

// FIXME
//  TEST_CASE("Split string by word") {
//   const std::string got = "aaaaaaa";
//   auto res = util::split_by_delimeter(got, "a");
//   CHECK(res.size() == 2);
//   CHECK(res[0] == "Hello");
//   CHECK(res[1] == "Here");
// }

TEST_SUITE_END();
