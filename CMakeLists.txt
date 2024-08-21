cmake_minimum_required(VERSION 3.23)
project(opengl_study CXX)

# CMake setup
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/examples.cmake)

# Libraries setup
set(GLFW_NO_GLU ON)
set(GLFW_INCLUDE_GLCOREARB ON)

find_package(fmt REQUIRED)
find_package(gsl-lite REQUIRED)
find_package(glfw3 REQUIRED)
find_package(FreeGLUT REQUIRED)
find_package(spdlog REQUIRED)
find_package(imgui REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_subdirectory(lib/dk)

file(GLOB imgui_bindings build/bindings/*)

example_exe("hello_world")
example_exe("first_triangle")
example_exe("simple_shader")
example_exe("tessellated_triangle")
example_exe("first_geometry_shader")
example_exe("true_triangle")
example_exe("simple_cube")
example_exe("spinning_cube")
example_exe("mesh_with_indices")
example_exe("textured_rectangle")
example_exe("test_colored_screen")
example_exe("rgb_normals")

message("Compiler: ${CMAKE_CXX_COMPILER}")
message("Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")

# enable_testing()
