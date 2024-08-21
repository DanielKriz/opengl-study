#ifndef DK_GL_LIGHT_HPP
#define DK_GL_LIGHT_HPP

#include <dklib/math/vector3d.hpp>

namespace dk::gl {
class LightSource {
public:
    [[nodiscard]] const math::Vector3D &get_ambient() const;
    [[nodiscard]] const math::Vector3D &get_diffuse() const;
    [[nodiscard]] const math::Vector3D &get_specular() const;
    [[nodiscard]] const math::Vector3D &get_position() const;

private:
    math::Vector3D ambient_;
    math::Vector3D diffuse_;
    math::Vector3D specular_;
    math::Vector3D position_;
};
} // namespace dk::gl

#endif // DK_GL_LIGHT_HPP
