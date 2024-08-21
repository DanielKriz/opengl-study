#include <doctest/doctest.h>
#include <dklib/blackboard.h>

#include <iostream>
#include <optional>

TEST_SUITE_BEGIN("BlackBoard");

TEST_CASE("Default constructor") { auto bb = dk::BlackBoard(); }

TEST_CASE("Set value with operator") {
    auto bb = dk::BlackBoard();
    std::string name = "new_type";
    bb.set<int>(name, 42);
    auto val = bb.get<int>(name).value();
}

TEST_CASE("Set value with operator") {
    auto bb = dk::BlackBoard();
    bb.set<int>("new", 42);
    auto val = bb.get<int>("new").value();
}

TEST_CASE("Return non-existent entry") {
    auto bb = dk::BlackBoard();
    auto val = bb.get<int>("non-existent");
    CHECK(val.has_value() == false);
}

TEST_CASE("Stream operator") {
    auto bb = dk::BlackBoard();
    bb.set<int>("new", 42);
    bb.set<float>("new2", 1.0f);
    bb.set<double>("new3", 1.312831238291);
    bb.set<std::string>("new4", "cool value");
}

TEST_CASE("Change stored value") {
    auto bb = dk::BlackBoard();
    bb.set<int>("test_value", 42);
    REQUIRE(bb.get<int>("test_value").value() == 42);
    bb.set<int>("test_value", 1);
    CHECK(bb.get<int>("test_value").value() == 1);
}

struct Base {
    Base() = default;
    Base(int x)
        : value_(x) {};
    void print() { std::cout << value_ << std::endl; }
    int get_value() const { return value_; }
    int value_;
};

TEST_CASE("_Blackboard with custom class") {
    // auto bb = dk::_BlackBoard<Base, int>();
    auto bb = dk::BlackBoard<Base, int, std::string>();
    bb.set<Base>("base_value", Base(42));
    bb.set<Base>("base_value_setted", 42);
    // This throws as it should be
    // It is created as an int, althrough I have called it with Base avlue
    // CHECK(bb.get<Base>("base_value_setted")->get_value() ==
    // bb.get<int>("incredible").value());
    bb.emplace<Base>("base_value_emplaced", 42);
    bb.set<int>("incredible", 42);
    bb.set<std::string>("str", "hello");

    CHECK(bb.get<Base>("base_value")->get_value() == bb.get<int>("incredible").value());
}

TEST_CASE("_Blackboard with custom class") {
    auto bb = dk::BlackBoard();
    bb.set<float>("base_value", 42);
    bb.set<int>("incredible", 42);

    CHECK(bb.get<float>("base_value") == bb.get<int>("incredible").value());
}

TEST_SUITE_END();
