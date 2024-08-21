#ifndef DK_MATH_POLYGON_HPP
#define DK_MATH_POLYGON_HPP

#include <dklib/math/point.h>
#include <vector>

class IPoint;

namespace dk::math::geometry {

class IPolygon {
public:
    IPolygon() = default;
    virtual ~IPolygon() = default;

    [[nodiscard]] virtual std::vector<IPoint> points() const = 0;

private:
};

class Polygon2D : public IPolygon {
public:
private:
};

class Polygon3D : public IPolygon {
public:
private:
};

} // namespace dk::math::geometry

#endif // DK_MATH_POLYGON_HPP
