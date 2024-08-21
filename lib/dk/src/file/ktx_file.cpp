#include <GL/gl.h>
#include <dklib/file/ktx_file.hpp>

using namespace dk::gl::types;

namespace dk::file::ktx {
enum class Endianness {
    BIG,
    LITTLE,
    UNKNOWN,
};

const u32 KTX_LITTLE_ENDIAN = 0x04030201;
const u32 KTX_BIG_ENDIAN = 0x01020304;
namespace {
    Endianness get_endianness(const Header &header) {
        switch (header.endianness) {
        case KTX_BIG_ENDIAN:
            return Endianness::BIG;
        case KTX_LITTLE_ENDIAN:
            return Endianness::LITTLE;
        default:
            return Endianness::UNKNOWN;
        }
    }
    u32 calculate_stride(const Header &header, u32 width, u32 padding = 4) {
        u32 channels = [&header]() -> u32 {
            switch (header.gl_base_internal_format) {
            case GL_RED:
                return 1;
            case GL_RG:
                return 2;
            case GL_BGR:
            case GL_RGB:
                return 3;
            case GL_BGRA:
            case GL_RGBA:
                return 4;
            }
            return 0;
        }();

        u32 stride = header.gl_type_size * channels * width;
        stride = (stride + (padding - 1)) & ~(padding - 1);

        return stride;
    }

    u32 calculate_face_size(const Header &header) {
        u32 stride = calculate_stride(header, header.pixel_width);
        return stride * header.pixel_height;
    }
} // namespace
} // namespace dk::file::ktx
