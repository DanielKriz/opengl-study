#ifndef DK_OBJ_FILE_HPP
#define DK_OBJ_FILE_HPP

#include "file_base.hpp"
#include <dklib/gl/gltypes.hpp>
#include <dklib/gl/mesh.hpp>
#include <dklib/gl/model.hpp>
#include <dklib/gl/vertex.hpp>

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <tuple>
#include <vector>

#include <spdlog/spdlog.h>

namespace dk {

struct Coordinates {
    gl::f32 x { 0.0 };
    gl::f32 y { 0.0 };
    gl::f32 z { 0.0 };
};

struct TextureCoordinates {
    gl::f32 u { 0.0 };
    gl::f32 v { 0.0 };
};

namespace file::obj::experimental {

    enum class DataType {
        VERTEX,
        NORMAL,
        TEXTURE,
        FACE,
        UNKNOWN,
    };

    math::Vector3D coordinates_from_stream_v2(std::stringstream &ss);

    TextureCoordinates tex_coordinates_from_stream(std::stringstream &ss);

    DataType match_data_type(std::string &str);

    std::tuple<gl::u32, gl::u32, gl::u32>
    get_indices_from_face(const std::string &face_str);

    template <typename VertexType = gl::Vertex, typename IndexType = gl::u32>
    gl::Mesh<VertexType, IndexType> read(const std::filesystem::path &filepath) {

        std::ifstream fin;
        fin.open(filepath);
        if (not fin.is_open()) {
            throw std::runtime_error("could not open the file");
        }

        std::vector<math::Vector3D> positions;
        std::vector<math::Vector3D> normals;
        std::vector<TextureCoordinates> textures;

        std::vector<IndexType> indices;

        std::vector<VertexType> vertices;

        std::map<std::tuple<gl::u32, gl::u32, gl::u32>, gl::u32> mmap;

        std::string line;
        while (std::getline(fin, line)) {
            std::stringstream ss(line);
            std::string prefix;
            ss >> prefix;
            switch (match_data_type(prefix)) {
            case DataType::VERTEX:
                positions.emplace_back(coordinates_from_stream_v2(ss));
                break;
            case DataType::NORMAL:
                normals.emplace_back(coordinates_from_stream_v2(ss));
                break;
            case DataType::TEXTURE:
                textures.emplace_back(tex_coordinates_from_stream(ss));
                break;
            case DataType::FACE:
                while (not ss.eof()) {
                    std::string face_str;
                    ss >> face_str;
                    const auto [pos, tex, norm] = get_indices_from_face(face_str);
                    if (auto it = mmap.find(std::make_tuple(pos, tex, norm));
                        it != mmap.end()) {
                        indices.push_back(it->second);
                        // spdlog::info("forced to not do this");
                        continue;
                    }
                    VertexType vertex;
                    vertex.position = positions[pos];
                    vertex.normal = normals[norm];
                    vertex.u = textures[tex].u;
                    vertex.v = textures[tex].v;
                    // vertices.emplace_back(positions[pos], normals[norm], textures[tex].u,
                    // textures[tex].v);
                    vertices.push_back(vertex);
                    mmap.insert({ std::make_tuple(pos, tex, norm), vertices.size() - 1 });
                    indices.push_back(vertices.size() - 1);
                }
            case DataType::UNKNOWN:
                continue;
            }
        }
        // for (auto idx : indices) {
        //     std::cout << idx << ' ';
        // }
        // std::cout << std::endl;
        // for (const auto &vertex : vertices) {
        //     std::cout << vertex.position << std::endl;
        //     std::cout << vertex.normal << std::endl;
        //     std::cout << vertex.u << ' ' << vertex.v << std::endl;
        // }
        return { vertices, indices };
    }
} // namespace file::obj::experimental

gl::Model load_obj_file(const std::string &file_path);

class ObjFile { //: public File {
private:
    enum class DataType {
        VERTEX,
        NORMAL,
        TEXTURE,
        FACE,
        UNKNOWN,
    };

public:
    virtual ~ObjFile() = default;

    static gl::TriangularMesh read(const std::string &filename);

private:
    static Coordinates coordinates_from_stream(std::stringstream &ss);
    static TextureCoordinates tex_coordinates_from_stream(std::stringstream &ss);
    static DataType match_data_type(std::string &str);
    /*
        std::vector<Coordinates> vertices;
        std::vector<Coordinates> normals;
        std::vector<TextureCoordinates> textures; */
};
} // namespace dk

#endif // DK_OBJ_FILE_HPP
