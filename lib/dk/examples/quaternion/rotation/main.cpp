#include <dklib/math.h>

#include <iostream>

using namespace dk::math;

int main() {
    auto vec = Vector3D(0.0f, 1.0f, 0.0f);
    std::cout << "original: " << vec << std::endl;
    std::cout << "rotated for 90 degrees over x axis: "
              << Quaternion::rotate(vec, 90_deg, Vector3D::x_axis()) << std::endl;
    std::cout << "rotated for 90 degrees over y axis: "
              << Quaternion::rotate(vec, 90_deg, Vector3D::y_axis()) << std::endl;
    std::cout << "rotated for 90 degrees over z axis: "
              << Quaternion::rotate(vec, 90_deg, Vector3D::z_axis()) << std::endl;
    return 0;
}
