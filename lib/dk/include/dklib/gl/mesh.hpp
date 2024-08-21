#ifndef DK_MESH_HPP
#define DK_MESH_HPP

#include <vector>

#include <dklib/gl/buffer_object.hpp>
#include <dklib/gl/texture.hpp>
#include <dklib/gl/vertex.hpp>

namespace dk::gl {

template <typename VertexType = Vertex, typename IndexType = u32>
class Mesh {
public:
    Mesh() = default;
    Mesh(const std::vector<VertexType> &vertices, const std::vector<IndexType> &indeces);

    void draw() const;

    const std::vector<VertexType> &get_vertices() const { return vertices_; }

private:
    void setup_mesh(std::vector<VertexType> vertices, std::vector<IndexType> indeces);

    VertexBuffer vbo;
    ElementBuffer ebo;

    std::vector<VertexType> vertices_;
    std::vector<IndexType> indices_;
    std::vector<Texture> textures;
};

template <typename VertexType, typename IndexType>
void Mesh<VertexType, IndexType>::setup_mesh(std::vector<VertexType> vertices, std::vector<IndexType> indices) { }

template <typename VertexType, typename IndexType>
Mesh<VertexType, IndexType>::Mesh(const std::vector<VertexType> &vertices, const std::vector<IndexType> &indices)
    : vertices_(vertices)
    , indices_(indices) {
    vbo.setup(vertices_);
    ebo.setup(indices_);
}

template <typename VertexType, typename IndexType>
void Mesh<VertexType, IndexType>::draw() const {
    glEnableVertexAttribArray(0);
    vbo.bind();
    experimental::bind_attributes_v2<VertexType>(0);
    ebo.bind();
    glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, nullptr);
    glDisableVertexAttribArray(0);
}

using TriangularMesh = Mesh<Vertex, u32>;

} // namespace dk::gl

#endif // DK_MESH_HPP
