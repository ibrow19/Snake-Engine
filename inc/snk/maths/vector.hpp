#ifndef SNAKE_VECTOR2_HEADER
#define SNAKE_VECTOR2_HEADER

#include <cmath>

namespace snk {

// Two dimensional vector.
template<typename T>
class Vector2 {
public:

    Vector2();

    // Using pass by value as vector is designed for use with primitives.
    Vector2(T x, T y);

public:

    T x;
    T y;
    
};


// TODO: potentially define more operations with dot product as needed.
//       e.g checking direction/collinearity/angle between vectors.


template<typename T>
T dot(const Vector2<T>& lhs, const Vector2<T>& rhs);

template<typename T>
T magnitude(const Vector2<T>& v);

template<typename T>
Vector2<T> operator-(const Vector2<T>& rhs);

template<typename T>
Vector2<T> operator+(const Vector2<T>& lhs, const Vector2<T>& rhs);

template<typename T>
Vector2<T> operator-(const Vector2<T>& lhs, const Vector2<T>& rhs);

template<typename T>
Vector2<T> operator*(const Vector2<T>& lhs, T rhs);

template<typename T>
Vector2<T> operator*(T lhs, const Vector2<T>& rhs);

template<typename T>
Vector2<T> operator/(const Vector2<T>& lhs, T rhs);

template<typename T>
Vector2<T>& operator+=(Vector2<T>& lhs, const Vector2<T>& rhs);

template<typename T>
Vector2<T>& operator-=(Vector2<T>& lhs, const Vector2<T>& rhs);

template<typename T>
Vector2<T>& operator*=(Vector2<T>& lhs, T rhs);

template<typename T>
Vector2<T>& operator/=(Vector2<T>& lhs, T rhs);

template<typename T>
bool operator==(const Vector2<T>& lhs, const Vector2<T>& rhs);

template<typename T>
bool operator!=(const Vector2<T>& lhs, const Vector2<T>& rhs);

// Define vector operations.
#include <snk/maths/vector.inl>

// Common vector types.
typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;

// Use vector for points.
template<typename T>
using Point2 = Vector2<T>;
typedef Point2<int> Point2i;
typedef Point2<float> Point2f;

} // namespace snk

#endif
