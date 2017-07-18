#include <cmath>
#include <iostream>
#include "maths/transform.hpp"

namespace snk {

Transform::Transform() 
: mMatrix{{1.f, 0.f, 0.f, 0.f}, 
          {0.f, 1.f, 0.f, 0.f},
          {0.f, 0.f, 1.f, 0.f},
          {0.f, 0.f, 0.f, 1.f}} {}


Transform::Transform(const TData& initData) 
: mMatrix{{1.f, 0.f, 0.f, 0.f}, 
          {0.f, 1.f, 0.f, 0.f},
          {0.f, 0.f, 1.f, 0.f},
          {0.f, 0.f, 0.f, 1.f}} {

    // Create matrix from translate origin -> scale -> rotation -> translation.
    float radian = initData.angle * M_PI / 180.f;
    float cos = std::cos(radian);
    float sin = std::sin(radian);
    float u0 = initData.scale.x * cos;
    float u1 = initData.scale.x * sin;
    float u2 = -initData.scale.y * sin;
    float u3 = initData.scale.y * cos;
    float tx = u0 * -initData.origin.x + u1 * -initData.origin.y + initData.translation.x;
    float ty = u2 * -initData.origin.x + u3 * -initData.origin.y + initData.translation.y;

    mMatrix[0][0] = u0;
    mMatrix[1][0] = u1;
    mMatrix[0][1] = u2;
    mMatrix[1][1] = u3;
    mMatrix[3][0] = tx;
    mMatrix[3][1] = ty;

}


const float* Transform::getMatrix() const {

    return mMatrix[0];

}


Transform& Transform::scale(float factor) {

    return scale(factor, factor);

}


Transform& Transform::scale(const Vector2f& factor) {

    return scale(factor.x, factor.y);

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

    Transform translation(x, y);
    return combine(translation);

}


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


Point2f Transform::transformPoint(const Point2f& p) const {

    return Vector2f(p.x * mMatrix[0][0] + p.y * mMatrix[1][0] + mMatrix[3][0],
                    p.x * mMatrix[0][1] + p.y * mMatrix[1][1] + mMatrix[3][1]);

}


Vector2f Transform::transformVector(const Vector2f& v) const {

    return Vector2f(v.x * mMatrix[0][0] + v.y * mMatrix[1][0],
                    v.x * mMatrix[0][1] + v.y * mMatrix[1][1]);

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


void Transform::printMatrix3() const {

    std::cout << mMatrix[0][0] << " | " << mMatrix[1][0] << " | " << mMatrix[3][0] << std::endl;
    std::cout << mMatrix[0][1] << " | " << mMatrix[1][1] << " | " << mMatrix[3][1] << std::endl;
    std::cout << mMatrix[0][3] << " | " << mMatrix[1][3] << " | " << mMatrix[3][3] << std::endl;

}


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


Point2f operator*(const Transform& lhs, const Point2f& rhs) {

    return lhs.transformPoint(rhs);

}

} // namespace snk
