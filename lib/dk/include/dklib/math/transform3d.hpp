#ifndef DK_TRANSFORM_3D_HPP
#define DK_TRANSFORM_3D_HPP

#include <dklib/math/matrix4d.hpp>
#include <dklib/math/quaternion.hpp>
#include <dklib/math/vector3d.hpp>

namespace dk {

class Transform3D {
public:
    Transform3D(math::Vector3D position, math::Vector3D scale, math::Quaternion rotation)
        : position_(std::move(position))
        , scale_(std::move(scale))
        , rotation_(std::move(rotation)) {};

    Transform3D()
        : position_(0.0f)
        , scale_(1.0f)
        , rotation_(1.0f, 0.0f, 0.0f, 0.0f) {};

    [[nodiscard]] math::Vector3D get_scale() const noexcept;
    void set_scale() noexcept;

    [[nodiscard]] math::Vector3D get_position() const noexcept;
    void set_position() noexcept;

    [[nodiscard]] math::Quaternion get_rotation() const noexcept;
    void set_rotation() noexcept;

    [[nodiscard]] math::Matrix4D get_transformation() const noexcept;

    [[nodiscard]] math::Vector3D forward() const noexcept;
    [[nodiscard]] math::Vector3D backward() const noexcept;
    [[nodiscard]] math::Vector3D up() const noexcept;
    [[nodiscard]] math::Vector3D down() const noexcept;
    [[nodiscard]] math::Vector3D right() const noexcept;
    [[nodiscard]] math::Vector3D left() const noexcept;

private:
    math::Vector3D position_;
    math::Vector3D scale_;
    math::Quaternion rotation_;
};

} // namespace dk

#endif // DK_TRANSFORM_3D_HPP
