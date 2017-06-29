#ifndef SNAKE_TRANSFORM_HEADER
#define SNAKE_TRANSFORM_HEADER

#include "vector.hpp"

namespace snk {

/// Matrix representing tranformaions in 2D space.
/// While a 3x3 matrix is sufficient to represent a 2D transformation, 
/// OpenGL, the library the snake engine uses for rendering, uses 4x4
/// matrices for all transformations (3D). Due to this, the class
/// internally uses a 4x4 column major matrix for ease of use with OpenGL.
class Transform {
public:

    /// Initialise transform with identity matrix.
    Transform();

    /// Get pointer to 4x4 matrix that can be used for openGL.
    const float* getMatrix() const;

    /// Uniform scale.
    Transform& scale(float factor);

    /// Scale.
    Transform& scale(float x, float y);

    /// Rotate.
    Transform& rotate(float angle);

    /// Translate using a vector.
    Transform& translate(const Vector2f& v);

    /// Translate using an offset on the x and y axis.
    Transform& translate(float x, float y);

    //// Combine transformations by multiplying them.
    Transform& combine(const Transform& t);

    /// Transform a vector using current transformation matrix.
    Vector2f transform(const Vector2f& v) const;

    // Matrix printing functions for debugging.
    /// Print 3x3 matrix.
    void printMatrix3() const;

    /// Print 4x4 matrix.
    void printMatrix4() const;

private:

    /// Manual initialisation of u and t.
    /// u represents scale and rotation.
    /// t represents translation.
    /// 4x4 matrix of form:
    /// u0 u2 0  tx
    /// u1 u3 0  ty
    /// 0  0  1  0
    /// 0  0  0  1
    Transform(float tx, float ty);

    Transform(float u0, float u1, 
              float u2, float u3);

    Transform(float u0, float u1, 
              float u2, float u3,
              float tx, float ty);

    /// Matrix in form usable by opengl.
    /// [column][row]
    float mMatrix[4][4];

};

Transform operator*(const Transform& lhs, const Transform& rhs);
Transform& operator*=(Transform& lhs, const Transform& rhs);

Vector2f operator*(const Transform& lhs, const Vector2f& rhs);

} // namespace snk

#endif
