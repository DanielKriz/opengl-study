#ifndef DK_SHAPE_HPP
#define DK_SHAPE_HPP

namespace dk::math {

class IShape {
public:
    virtual ~IShape() = default;
    [[nodiscard]] virtual double area() const = 0;
    [[nodiscard]] virtual double perimeter() const = 0;

protected:
private:
};

class IShape2D : public IShape {
public:
    virtual ~IShape2D() = default;

protected:
private:
};

class IShape3D : public IShape {
public:
    virtual ~IShape3D() = default;

protected:
private:
};

} // namespace dk::math

#endif // DK_SHAPE_HPP
