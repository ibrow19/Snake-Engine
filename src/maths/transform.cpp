#include <cmath>
#include <iostream>
#include "maths/transform.hpp"

namespace snk {

/// Initialise transform with identity matrix.
Transform::Transform() 
: mMatrix{{1.f, 0.f, 0.f, 0.f}, 
          {0.f, 1.f, 0.f, 0.f},
          {0.f, 0.f, 1.f, 0.f},
          {0.f, 0.f, 0.f, 1.f}} {}


const float* Transform::getMatrix() const {

    return mMatrix[0];

}


Transform& Transform::scale(float factor) {

    return scale(factor, factor);

}


Transform& Transform::scale(float x, float y) {

    Transform scaler(x, 0.f,
                     0.f, y);
    return combine(scaler);

}


Transform& Transform::rotate(float angle) {

    float radian = angle * M_PI / 180.f;
    float cos = std::cos(radian);
    float sin = std::sin(radian);

    Transform rotation(cos, sin,
                       -sin, cos);
    return combine(rotation);


}


Transform& Transform::translate(const Vector2f& v) {

    return translate(v.x, v.y);

}


Transform& Transform::translate(float x, float y) {

    mMatrix[3][0] += x;
    mMatrix[3][1] += y;
    return *this;

}


//// Combine transformations by multiplying them.
Transform& Transform::combine(const Transform& t) {

    const float (*a)[4] = mMatrix;
    const float (*b)[4] = t.mMatrix;

    // Only need to combine used elements (u and t);
    *this = Transform(a[0][0] * b[0][0] + a[1][0] * b[0][1],  // u0
                      a[0][1] * b[0][0] + a[1][1] * b[0][1],  // u1
                      a[0][0] * b[1][0] + a[1][0] * b[1][1],  // u2
                      a[0][1] * b[1][0] + a[1][1] * b[1][1],  // u3
                      a[0][0] * b[3][0] + a[1][0] * b[3][1] + a[3][0],  // tx
                      a[0][1] * b[3][0] + a[1][1] * b[3][1] + a[3][1]); // ty
    return *this;

}


/// Transform a vector using current transformation matrix.
Vector2f Transform::transform(const Vector2f& v) const {

    return Vector2f(v.x * mMatrix[0][0] + v.y * mMatrix[1][0] + mMatrix[3][0],
                    v.x * mMatrix[0][1] + v.y * mMatrix[1][1] + mMatrix[3][1]);

}


Transform::Transform(float tx, float ty)
: mMatrix{{1.f, 0.f, 0.f, 0.f},
          {0.f, 1.f, 0.f, 0.f},
          {0.f, 0.f, 1.f, 0.f},
          {tx, ty, 0.f, 1.f}} {}


Transform::Transform(float u0, float u1, 
                     float u2, float u3)
: mMatrix{{u0,  u1,  0.f, 0.f},
          {u2,  u3,  0.f, 0.f},
          {0.f, 0.f, 1.f, 0.f},
          {0.f, 0.f, 0.f, 1.f}} {}


Transform::Transform(float u0, float u1, 
                     float u2, float u3,
                     float tx, float ty)
: mMatrix{{u0,  u1,  0.f, 0.f},
          {u2,  u3,  0.f, 0.f},
          {0.f, 0.f, 1.f, 0.f},
          {tx,  ty,  0.f, 1.f}} {}


/// Print 3x3 matrix.
void Transform::printMatrix3() const {

    std::cout << mMatrix[0][0] << " | " << mMatrix[1][0] << " | " << mMatrix[3][0] << std::endl;
    std::cout << mMatrix[0][1] << " | " << mMatrix[1][1] << " | " << mMatrix[3][1] << std::endl;
    std::cout << mMatrix[0][3] << " | " << mMatrix[1][3] << " | " << mMatrix[3][3] << std::endl;

}

/// Print 4x4 matrix.
void Transform::printMatrix4() const {

    std::cout << mMatrix[0][0] << " | " << mMatrix[1][0] << " | " << mMatrix[2][0] << " | " << mMatrix[3][0] << std::endl;
    std::cout << mMatrix[0][1] << " | " << mMatrix[1][1] << " | " << mMatrix[2][1] << " | " << mMatrix[3][1] << std::endl;
    std::cout << mMatrix[0][2] << " | " << mMatrix[1][2] << " | " << mMatrix[2][2] << " | " << mMatrix[3][2] << std::endl;
    std::cout << mMatrix[0][3] << " | " << mMatrix[1][3] << " | " << mMatrix[2][3] << " | " << mMatrix[3][3] << std::endl;
}


Transform operator*(const Transform& lhs, const Transform& rhs) {

    return Transform(lhs).combine(rhs);;

}


Transform& operator*=(Transform& lhs, const Transform& rhs) {

    return lhs.combine(rhs);

}


Vector2f operator*(const Transform& lhs, const Vector2f& rhs) {

    return lhs.transform(rhs);

}

    
} // namespace snk
