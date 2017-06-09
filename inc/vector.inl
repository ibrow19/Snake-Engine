#include <cmath>


template<typename T>
Vector2d<T>::Vector2d()
: x(T(0)),
  y(T(0)) {}


template<typename T>
Vector2d<T>::Vector2d(T x, T y)
: x(x),
  y(y) {}


template<typename T>
T dot(const Vector2d<T>& lhs, const Vector2d<T>& rhs) {

    return (lhs.x * rhs.x + lhs.y * rhs.y);

}


template<typename T>
T magnitude(const Vector2d<T>& v) {

    return sqrt(pow(v.x, 2) + pow(v.y, 2));

}


template<typename T>
Vector2d<T> operator-(const Vector2d<T>& rhs) {

    return Vector2d<T>(-rhs.x, -rhs.y);

}


template<typename T>
Vector2d<T> operator+(const Vector2d<T>& lhs, const Vector2d<T>& rhs) {

    return Vector2d<T>(lhs.x + rhs.x, lhs.y + rhs.y);

}


template<typename T>
Vector2d<T> operator-(const Vector2d<T>& lhs, const Vector2d<T>& rhs) {

    return Vector2d<T>(lhs.x - rhs.x, lhs.y - rhs.y);

}


template<typename T>
Vector2d<T> operator*(const Vector2d<T>& lhs, T rhs) {

    return Vector2d<T>(lhs.x * rhs, lhs.y * rhs);

}


template<typename T>
Vector2d<T> operator*(T lhs, const Vector2d<T>& rhs) {

    return Vector2d<T>(rhs.x * lhs, rhs.y * lhs);

}


template<typename T>
Vector2d<T> operator/(const Vector2d<T>& lhs, T rhs) {

    return Vector2d<T>(lhs.x / rhs, lhs.y / rhs);

}


template<typename T>
Vector2d<T>& operator+=(Vector2d<T>& lhs, const Vector2d<T>& rhs) {

    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;

}


template<typename T>
Vector2d<T>& operator-=(Vector2d<T>& lhs, const Vector2d<T>& rhs) {

    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;

}


template<typename T>
Vector2d<T>& operator*=(Vector2d<T>& lhs, T rhs) {

    lhs.x *= rhs;
    lhs.y *= rhs;
    return lhs;

}


template<typename T>
Vector2d<T>& operator/=(Vector2d<T>& lhs, T rhs) {

    lhs.x /= rhs;
    lhs.y /= rhs;
    return lhs;

}


template<typename T>
bool operator==(const Vector2d<T>& lhs, const Vector2d<T>& rhs) {

    return (lhs.x == rhs.x) && (lhs.y == rhs.y);

}


template<typename T>
bool operator!=(const Vector2d<T>& lhs, const Vector2d<T>& rhs) {

    return !(lhs == rhs);

}
