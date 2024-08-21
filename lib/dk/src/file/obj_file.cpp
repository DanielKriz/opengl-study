#include <iomanip>
#include <dklib/file/obj_file.hpp>
#include <dklib/gl/gltypes.hpp>
#include <dklib/gl/vertex.hpp>

#include <dklib/util.h>

#include <filesystem>

namespace dk {

namespace file::obj::experimental {

    enum class VertexLayout {};

    /* template <typename VertexType, typename IndexType = gl::u32>
    gl::Mesh<VertexType, IndexType> read(const std::filesystem::path &filepath) { }
    */

    math::Vector3D coordinates_from_stream_v2(std::stringstream &ss) {
        math::Vector3D coords;
        ss >> coords.x >> coords.y >> coords.z;
        return coords;
    };

    TextureCoordinates tex_coordinates_from_stream(std::stringstream &ss) {
        TextureCoordinates coords;
        ss >> coords.u >> coords.v;
        return coords;
    };

    DataType match_data_type(std::string &str) {
        if (str == "v") {
            return DataType::VERTEX;
        } else if (str == "vn") {
            return DataType::NORMAL;
        } else if (str == "vt") {
            return DataType::TEXTURE;
        } else if (str == "f") {
            return DataType::FACE;
        } else {
            return DataType::UNKNOWN;
        }
    }

    std::tuple<gl::u32, gl::u32, gl::u32>
    get_indices_from_face(const std::string &face_str) {
        auto tmp_indices = util::strs_to_ints(util::split_by_delimeter(face_str, "/"));

        static const gl::u32 DEFAULT_FACE_COMPONENT_COUNT = 3;
        if (tmp_indices.size() != DEFAULT_FACE_COMPONENT_COUNT) {
            // for (auto s : util::split_by_delimeter(face_str, "/")) {
            //     std::cout << std::quoted(s) << ' ';
            // }
            // std::cout << std::endl;
            throw std::runtime_error("Wrong count of face components " + face_str);
        }

        // OBJ files are indexed from 1, but we want them to be indexed from 0
        return { tmp_indices[0] - 1, tmp_indices[1] - 1, tmp_indices[2] - 1 };
    }
    /*
        template <typename VertexType, typename IndexType>
        gl::Mesh<VertexType, IndexType> read(const std::filesystem::path &filepath)
       {
        } */

} // namespace file::obj::experimental

gl::TriangularMesh ObjFile::read(const std::string &filepath) {
    std::ifstream fin;
    fin.open(filepath);

    spdlog::info("Opening a file: {}", filepath);

    if (not fin.is_open()) {
        throw std::runtime_error("could not open the file");
    }

    std::vector<Coordinates> positions;
    std::vector<Coordinates> normals;
    std::vector<TextureCoordinates> textures;

    const auto process_face = [](std::stringstream &ss) {
        std::vector<gl::u32> indeces;
        while (not ss.eof()) {
            std::string vertex_str;
            ss >> vertex_str;
            auto tmp_indices = util::strs_to_ints(util::split_by_delimeter(vertex_str, "/"));
            indeces.push_back(tmp_indices[0] - 1);
        }
        return indeces;
    };

    std::vector<gl::Vertex> vertices;
    std::vector<gl::u32> indeces;

    // f 1/2/3 -> f vertex/texture/normal

    std::string line;
    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;
        switch (match_data_type(prefix)) {
        case DataType::VERTEX:
            positions.emplace_back(coordinates_from_stream(ss));
            break;
        case DataType::NORMAL:
            normals.emplace_back(coordinates_from_stream(ss));
            break;
        case DataType::TEXTURE:
            textures.emplace_back(tex_coordinates_from_stream(ss));
            break;
        case DataType::FACE:
            for (const auto index : process_face(ss)) {
                indeces.push_back(index);
            }
        case DataType::UNKNOWN:
            continue;
        }
    }

    // TODO: this is not all
#if 0
    for (const auto &pos : positions) {
        gl::Vertex tmp;
        tmp.position = math::Vector3D(pos.x, pos.y, pos.z);
        vertices.push_back(tmp);
    }
#else
    for (const auto &pos : positions) {
        gl::Vertex tmp;
        tmp.position[0] = pos.x;
        tmp.position[1] = pos.y;
        tmp.position[2] = pos.z;
        vertices.push_back(tmp);
    }
#endif
    return { vertices, indeces };
}

Coordinates ObjFile::coordinates_from_stream(std::stringstream &ss) {
    Coordinates coords;
    ss >> coords.x >> coords.y >> coords.z;
    return coords;
};

TextureCoordinates ObjFile::tex_coordinates_from_stream(std::stringstream &ss) {
    TextureCoordinates coords;
    ss >> coords.u >> coords.v;
    return coords;
};

ObjFile::DataType ObjFile::match_data_type(std::string &str) {
    if (str == "v") {
        return DataType::VERTEX;
    } else if (str == "vn") {
        return DataType::NORMAL;
    } else if (str == "vt") {
        return DataType::TEXTURE;
    } else if (str == "f") {
        return DataType::FACE;
    } else {
        return DataType::UNKNOWN;
    }
}

// std::istream &operator>>(std::istream &in, ObjFile &obj_file) { }

} // namespace dk
