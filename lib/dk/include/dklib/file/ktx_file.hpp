#ifndef DK_KTX_FILE_HPP
#define DK_KTX_FILE_HPP

#include <dklib/gl/gltypes.hpp>

namespace dk::file::ktx {

struct Header {
    char identifier[12];
    gl::u32 endianness;
    gl::u32 gltype;
    gl::u32 gl_type_size;
    gl::u32 glformat;
    gl::u32 glinternalformat;
    gl::u32 gl_base_internal_format;
    gl::u32 pixel_width;
    gl::u32 pixel_height;
    gl::u32 pixel_depth;
    gl::u32 arrayelements;
    gl::u32 faces;
    gl::u32 miplevels;
    gl::u32 keypairbytes;
};

gl::u32 load(const std::string &filename);
bool save(const std::string &filename);

} // namespace dk::file::ktx

#endif // DK_KTX_FILE_HPP
