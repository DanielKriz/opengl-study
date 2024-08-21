#include <doctest/doctest.h>
#include <dklib/dklib.h>

#include <filesystem>
#include <vector>

using namespace dk::gl::types;
using namespace dk::util;

const std::string mock_file_path = std::string { std::filesystem::current_path() } + "/lib/rat/tests/mocks/vertices.txt";
