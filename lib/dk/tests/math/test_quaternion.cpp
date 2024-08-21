#include <doctest/doctest.h>
#include <dklib/math.h>

#include <cmath>
#include <numbers>
#include <sstream>

using namespace dk::math;
using std::numbers::pi;

constexpr float eps = 0.000001f;

TEST_SUITE_BEGIN("Quaternion");

TEST_CASE("Basic constructor") {
    auto quat = Quaternion(1.0f, 2.0f, 3.0f, 4.0f);
    CHECK(quat.imag.x == 1.0f);
    CHECK(quat.imag.y == 2.0f);
    CHECK(quat.imag.z == 3.0f);
    CHECK(quat.real == 4.0f);
}

TEST_CASE("Constructor from vector and scalar") {
    auto quat = Quaternion({ 1.0f, 2.0f, 3.0f }, 4.0f);
    CHECK(quat.imag.x == 1.0f);
    CHECK(quat.imag.y == 2.0f);
    CHECK(quat.imag.z == 3.0f);
    CHECK(quat.real == 4.0f);
}

TEST_CASE("Constructor from vector and scalar lvalues") {
    auto vec = Vector3D(1.0f, 2.0f, 3.0f);
    auto scalar = 4.0f;
    auto quat = Quaternion(vec, scalar);
    CHECK(quat.imag.x == 1.0f);
    CHECK(quat.imag.y == 2.0f);
    CHECK(quat.imag.z == 3.0f);
    CHECK(quat.real == 4.0f);
}

TEST_CASE("Unit quaternion") {
    auto quat = Quaternion(Vector3D::zero(), 1.0f);
    CHECK(quat.is_unit() == true);
}

TEST_CASE("Not a unit quaternion") {
    auto quat = Quaternion(4.0f, 3.0f, 2.0f, 1.0f);
    CHECK(quat.is_unit() == false);
}

TEST_CASE("Equality operator") {
    auto quat = Quaternion(1.0f, 1.0f, 1.0f, 1.0f);
    auto copy = quat;
    CHECK(quat == copy);
}

TEST_CASE("Failing equality operator") {
    auto quat1 = Quaternion(1.0f, 1.0f, 1.0f, 1.0f);
    auto quat2 = Quaternion(2.0f, 1.0f, 1.0f, 1.0f);
    CHECK((quat1 == quat2) == false);
}

TEST_CASE("Failing inequality operator") {
    auto quat = Quaternion(1.0f, 1.0f, 1.0f, 1.0f);
    auto copy = quat;
    CHECK((quat != copy) == false);
}

TEST_CASE("Inequality operator") {
    auto quat1 = Quaternion(1.0f, 1.0f, 1.0f, 1.0f);
    auto quat2 = Quaternion(2.0f, 1.0f, 1.0f, 1.0f);
    CHECK(quat1 != quat2);
}

TEST_CASE("Normalized") {
    auto quat1 = Quaternion(1.0f, 1.0f, 1.0f, 1.0f);
    auto quat2 = quat1.normalized();
    CHECK(quat1 != quat2);
    CHECK(quat2.imag.x == doctest::Approx(0.5f));
    CHECK(quat2.imag.y == doctest::Approx(0.5f));
    CHECK(quat2.imag.z == doctest::Approx(0.5f));
    CHECK(quat2.real == doctest::Approx(0.5f));
}

TEST_CASE("Normalized throws on zero division") {
    CHECK_THROWS_AS(
        {
            auto quat = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
            [[maybe_unused]] auto n_quat = quat.normalized();
        },
        std::runtime_error
    );
}

TEST_CASE("Normalized should preserve the original vector") {
    auto quat = Quaternion(1.0f, 1.0f, 1.0f, 1.0f);
    auto c_quat = quat;
    auto n_quat = quat.normalized();
    CHECK(quat == c_quat);
    CHECK(quat != n_quat);
}

TEST_CASE("Normalize should not preserve the original vector") {
    auto quat = Quaternion(1.0f, 1.0f, 1.0f, 1.0f);
    auto c_quat = quat;
    auto n_quat = quat.normalize();
    quat.normalize();
    CHECK(quat != c_quat);
    CHECK(quat == n_quat);
}

TEST_CASE("Normalize throws on zero division") {
    CHECK_THROWS_AS(
        {
            auto quat = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
            quat.normalize();
        },
        std::runtime_error
    );
}

TEST_CASE("Computation of a norm") {
    auto quat = Quaternion(1.0f, 1.0f, 1.0f, 1.0f);
    CHECK(quat.norm() == std::sqrt(3.0f + 1.0f));
}

TEST_CASE("Getter for vector part") {
    auto quat = Quaternion(1.0f, 1.0f, 1.0f, 1.0f);
    auto vec = quat.vector_part();
    CHECK(vec == Vector3D::unit());
}

TEST_CASE("Getter for vector part creates a copy") {
    auto quat = Quaternion(1.0f, 1.0f, 1.0f, 1.0f);
    auto vec = quat.vector_part();
    vec.x = 42.0f;
    CHECK(quat == Quaternion(1.0f, 1.0f, 1.0f, 1.0f));
}

TEST_CASE("Conjugative of a quaternion") {
    auto quat = Quaternion(1.0f, 1.0f, 1.0f, 1.0f);
    auto conj = quat.conjugate();
    CHECK(quat != conj);
    CHECK(conj.imag.x == -1.0f);
    CHECK(conj.imag.y == -1.0f);
    CHECK(conj.imag.z == -1.0f);
    CHECK(conj.real == 1.0f);
}

TEST_CASE("Conjugative of zero quaternion") {
    auto quat = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
    auto conj = quat.conjugate();
    CHECK(quat == conj);
}

TEST_CASE("Predicate whether quaternion is pure") {
    auto quat = Quaternion(1.0f, 1.0f, 1.0f, 0.0f);
    CHECK(quat.is_pure());
}

TEST_CASE("Failing predicate whether quaternion is pure") {
    auto quat = Quaternion(1.0f, 1.0f, 1.0f, 1.0f);
    CHECK(quat.is_pure() == false);
}

// TODO
// TEST_CASE(Quaternion, inverse) {
//     auto quat = Quaternion(1.0f, 2.0f, 3.0f, 4.0f);
// }

TEST_CASE("Add operator") {
    auto quat = Quaternion(1.0f, 1.0f, 1.0f, 1.0f) + Quaternion(1.0f, 1.0f, 1.0f, 1.0f);
    CHECK(quat == Quaternion(2.0f, 2.0f, 2.0f, 2.0f));
}

TEST_CASE("Sub operator") {
    auto quat = Quaternion(1.0f, 1.0f, 1.0f, 1.0f) - Quaternion(1.0f, 1.0f, 1.0f, 1.0f);
    CHECK(quat == Quaternion(0.0f, 0.0f, 0.0f, 0.0f));
}

TEST_CASE("Add with self assign operator") {
    auto quat = Quaternion(1.0f, 1.0f, 1.0f, 1.0f);
    quat += Quaternion(1.0f, 1.0f, 1.0f, 1.0f);
    CHECK(quat == Quaternion(2.0f, 2.0f, 2.0f, 2.0f));
}

TEST_CASE("Sub with self assign operator") {
    auto quat = Quaternion(1.0f, 1.0f, 1.0f, 1.0f);
    quat -= Quaternion(1.0f, 1.0f, 1.0f, 1.0f);
    CHECK(quat == Quaternion(0.0f, 0.0f, 0.0f, 0.0f));
}

// TODO: needs refactoring
// TEST_CASE(Quaternion, unit_norm) {
//     auto quat = Quaternion(1.0f, 1.0f, 1.0f, 1.0f);
//     auto uquat = quat.unit_norm();
//     CHECK(uquat.imag.x == uquat.imag.y and uquat.imag.x == uquat.imag.z);
//     CHECK(uquat.imag.x == 0.00290885f, eps);
//     CHECK(uquat.real == 0.999962f, eps);
// }
//
// TEST_CASE(Quaternion, to_unit_norm) {
//     auto quat = Quaternion(1.0f, 1.0f, 1.0f, 1.0f);
//     quat.to_unit_norm();
//     CHECK(quat.imag.x == quat.imag.y and quat.imag.x == quat.imag.z);
//     CHECK(quat.imag.x == 0.00290885f, eps);
//     CHECK(quat.real == 0.999962f, eps);
// }

TEST_CASE("Creation of pure vector") {
    auto quat = Quaternion(1.0f, 1.0f, 1.0f, 1.0f);
    auto pure = quat.pure();
    CHECK(pure == Quaternion(1.0f, 1.0f, 1.0f, 0.0f));
    CHECK(pure.is_pure());
}

TEST_CASE("Change to a pure vector") {
    auto quat = Quaternion(1.0f, 1.0f, 1.0f, 1.0f);
    quat.to_pure();
    CHECK(quat == Quaternion(1.0f, 1.0f, 1.0f, 0.0f));
    CHECK(quat.is_pure());
}

TEST_CASE("Rotation of a vector") {
    auto vec = Vector3D(0.0f, 1.0f, 0.0f);
    // FIXME
    auto axis = Vector3D::x_axis();
    auto rotated = Quaternion::rotate(vec, 90.0_deg, axis);
    CHECK(rotated.x == doctest::Approx(0.0f));
    CHECK(rotated.y == doctest::Approx(0.0f));
    CHECK(rotated.z == doctest::Approx(1.0f));
}

TEST_CASE("Compatibility with streams") {
    auto quat = Quaternion(1.0f, 2.0f, 3.0f, 4.0f);
    std::ostringstream oss;
    oss << quat;
    CHECK("(1, 2, 3, 4)" == oss.str());
}

TEST_SUITE_END();
