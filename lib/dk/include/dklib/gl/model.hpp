#ifndef DK_GL_MODEL_HPP
#define DK_GL_MODEL_HPP

#include <vector>

#include <dklib/gl/gltypes.hpp>
#include <dklib/gl/mesh.hpp>
#include <dklib/gl/texture.hpp>
#include <dklib/gl/vertex.hpp>

namespace dk::gl {
struct Model {
    std::vector<Vertex> vertices;
    std::vector<u32> indeces;
};
} // namespace dk::gl

#endif // DK_GL_MODEL_HPP
