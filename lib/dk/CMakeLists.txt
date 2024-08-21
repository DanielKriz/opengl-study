include(cmake/docs.cmake)

file(GLOB SRC_FILES "src/*.cpp" "src/**/*.cpp")
file(GLOB HDR_FILES "include/**/*.hpp" "include/**/*.h")
file(GLOB imgui_bindings "${CMAKE_BINARY_DIR}/bindings/*")

function(dklib_example arg)
    message("Setting up DKLib Example '${arg}'")
    file(GLOB EXAMPLE_SRC_FILES examples/${arg}/*.cpp)
    file(GLOB EXAMPLE_HDR_FILES examples/${arg}/*.hpp)

    add_executable(
        ${arg}
        ${EXAMPLE_SRC_FILES}
        ${EXAMPLE_HDR_FILES}
    )
    set_target_properties(
        ${arg}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples/dklib"
        LINKER_LANGUAGE CXX
    )
    target_link_libraries(
        ${arg}
        PUBLIC dk
        spdlog::spdlog
    )
endfunction()

add_library(dk ${SRC_FILES} ${HDR_FILES} ${imgui_bindings})

target_include_directories(
    dk
    PUBLIC
    include/
    ${CMAKE_BINARY_DIR}/bindings
)
target_link_libraries(
    dk
    glfw
    fmt::fmt
    spdlog::spdlog
    imgui::imgui
    SDL2::SDL2main
    SDL2::SDL2-static
)

# set(DO_BUILD_DOCS 1)

if (DEFINED DO_BUILD_DOCS)
    dk_enable_doxygen()
endif()

# Examples
dklib_example("obj_file")


# Testing Setup
file(GLOB TEST_SRC_FILES "tests/*.cpp" "tests/**/*.cpp")
file(GLOB TEST_HDR_FILES "tests/*.hpp" "tests/**/*.hpp")

find_package(doctest REQUIRED)
include(doctest)

set(DK_TEST_NAME "test_dklib")
add_executable(
    ${DK_TEST_NAME}
    ${TEST_SRC_FILES}
    ${TEST_HDR_FILES}
)
set_target_properties(
    ${DK_TEST_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests"
    LINKER_LANGUAGE CXX
)

target_link_libraries(${DK_TEST_NAME} PUBLIC
    dk
    SDL2::SDL2main
)
target_link_libraries(${DK_TEST_NAME} PRIVATE doctest::doctest)
enable_testing()
doctest_discover_tests(${DK_TEST_NAME})
