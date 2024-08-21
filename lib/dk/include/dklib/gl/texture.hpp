#ifndef DK_TEXTURE_HPP
#define DK_TEXTURE_HPP

#include <dklib/gl/gltypes.hpp>
#include <string>

namespace dk::gl {

enum class TextureType : enum32 {
    TEX_1D = GL_TEXTURE_1D,
    TEX_2D = GL_TEXTURE_2D,
    TEX_3D = GL_TEXTURE_3D,
    RECTANGLE = GL_TEXTURE_RECTANGLE,
    CUBE_MAP = GL_TEXTURE_CUBE_MAP,
    TEX_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
    TEX_2D_ARRAY = GL_TEXTURE_2D_ARRAY,
    CUBE_MAP_ARRAY = GL_TEXTURE_CUBE_MAP_ARRAY,
    TEX_2D_MULTISAMPLE = GL_TEXTURE_2D_MULTISAMPLE,
    TEX_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
};

struct Texture {
    std::size_t id;
    std::string type;
};

class TextureManager {
public:
private:
};

} // namespace dk::gl

#endif // DK_TEXTURE_HPP
