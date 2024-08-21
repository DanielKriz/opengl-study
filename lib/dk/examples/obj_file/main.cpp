#include <dklib/file/obj_file.hpp>
#include <dklib/gl/vertex.hpp>

int main() {
    auto vertices = dk::file::obj::experimental::read<dk::gl::experimental::Vertex>(
        "assets/obj_files/cube.obj"
    );
    for (const auto &vertex : vertices.get_vertices()) {
        std::cout << vertex.position << std::endl;
        std::cout << vertex.normal << std::endl;
        std::cout << vertex.u << ' ' << vertex.v << std::endl;
    }
}
