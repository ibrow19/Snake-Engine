#ifndef VECTOR2D_HEADER
#define VECTOR2D_HEADER


// Two dimensional vector.
template<typename T>
class Vector2d {
public:

    Vector2d();

    // Using pass by value as vector is designed for use with primitives.
    Vector2d(T x, T y);

public:

    T x;
    T y;
    
};


// TODO: potentially define more operations with dot product as needed.
//       e.g checking direction/collinearity/angle between vectors.


template<typename T>
T dot(const Vector2d<T>& lhs, const Vector2d<T>& rhs);

template<typename T>
T magnitude(const Vector2d<T>& v);

template<typename T>
Vector2d<T> operator-(const Vector2d<T>& rhs);

template<typename T>
Vector2d<T> operator+(const Vector2d<T>& lhs, const Vector2d<T>& rhs);

template<typename T>
Vector2d<T> operator-(const Vector2d<T>& lhs, const Vector2d<T>& rhs);

template<typename T>
Vector2d<T> operator*(const Vector2d<T>& lhs, T rhs);

template<typename T>
Vector2d<T> operator*(T lhs, const Vector2d<T>& rhs);

template<typename T>
Vector2d<T> operator/(const Vector2d<T>& lhs, T rhs);

template<typename T>
Vector2d<T>& operator+=(const Vector2d<T>& lhs, const Vector2d<T>& rhs);

template<typename T>
Vector2d<T>& operator-=(const Vector2d<T>& lhs, const Vector2d<T>& rhs);

template<typename T>
Vector2d<T>& operator*=(const Vector2d<T>& lhs, const Vector2d<T>& rhs);

template<typename T>
Vector2d<T>& operator/=(const Vector2d<T>& lhs, const Vector2d<T>& rhs);

template<typename T>
Vector2d<T>& operator*=(const Vector2d<T>& lhs, T rhs);

template<typename T>
Vector2d<T>& operator/=(const Vector2d<T>& lhs, T rhs);

template<typename T>
bool operator==(const Vector2d<T>& lhs, const Vector2d<T>& rhs);

template<typename T>
bool operator!=(const Vector2d<T>& lhs, const Vector2d<T>& rhs);


#include "vector.inl"


typedef Vector2d<int> Vector2di;
typedef Vector2d<float> Vector2df;


#endif
