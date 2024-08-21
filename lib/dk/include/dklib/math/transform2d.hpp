#ifndef DK_TRANSFORM_2D_HPP
#define DK_TRANSFORM_2D_HPP

#include <dklib/math/angle.hpp>
#include <dklib/math/matrix3d.hpp>
#include <dklib/math/vector2d.hpp>

namespace dk {

class Transform2D {
public:
    constexpr Transform2D(math::Vector2D position, math::Vector2D scale, math::Radians rotation)
        : position_(std::move(position))
        , scale_(std::move(scale))
        , rotation_(std::move(rotation)) {};

    // TODO
    // Transform2D()
    //     : position_(0.0f)
    //     , scale_(1.0f)
    //     , rotation_(1.0f, 0.0f, 0.0f, 0.0f) {};

    [[nodiscard]] math::Vector2D get_scale() const noexcept;
    void set_scale() noexcept;

    [[nodiscard]] math::Vector2D get_position() const noexcept;
    void set_position() noexcept;

    [[nodiscard]] math::Radians get_rotation() const noexcept;
    void set_rotation() noexcept;

    [[nodiscard]] math::Matrix3D get_transformation() const noexcept;

    [[nodiscard]] math::Vector2D forward() const noexcept;
    [[nodiscard]] math::Vector2D backward() const noexcept;
    [[nodiscard]] math::Vector2D up() const noexcept;
    [[nodiscard]] math::Vector2D down() const noexcept;
    [[nodiscard]] math::Vector2D right() const noexcept;
    [[nodiscard]] math::Vector2D left() const noexcept;

private:
    math::Vector2D position_;
    math::Vector2D scale_;
    math::Radians rotation_;
};

} // namespace dk

#endif // DK_TRANSFORM_2D_HPP
