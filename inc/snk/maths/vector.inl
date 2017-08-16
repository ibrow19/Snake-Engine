template<typename T>
Vector2<T>::Vector2()
: x(T(0)),
  y(T(0)) {}


template<typename T>
Vector2<T>::Vector2(T x, T y)
: x(x),
  y(y) {}


template<typename T>
T dot(const Vector2<T>& lhs, const Vector2<T>& rhs) {

    return (lhs.x * rhs.x + lhs.y * rhs.y);

}


template<typename T>
T magnitude(const Vector2<T>& v) {

    return sqrt(pow(v.x, 2) + pow(v.y, 2));

}


template<typename T>
Vector2<T> operator-(const Vector2<T>& rhs) {

    return Vector2<T>(-rhs.x, -rhs.y);

}


template<typename T>
Vector2<T> operator+(const Vector2<T>& lhs, const Vector2<T>& rhs) {

    return Vector2<T>(lhs.x + rhs.x, lhs.y + rhs.y);

}


template<typename T>
Vector2<T> operator-(const Vector2<T>& lhs, const Vector2<T>& rhs) {

    return Vector2<T>(lhs.x - rhs.x, lhs.y - rhs.y);

}


template<typename T>
Vector2<T> operator*(const Vector2<T>& lhs, T rhs) {

    return Vector2<T>(lhs.x * rhs, lhs.y * rhs);

}


template<typename T>
Vector2<T> operator*(T lhs, const Vector2<T>& rhs) {

    return Vector2<T>(rhs.x * lhs, rhs.y * lhs);

}


template<typename T>
Vector2<T> operator/(const Vector2<T>& lhs, T rhs) {

    return Vector2<T>(lhs.x / rhs, lhs.y / rhs);

}


template<typename T>
Vector2<T>& operator+=(Vector2<T>& lhs, const Vector2<T>& rhs) {

    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;

}


template<typename T>
Vector2<T>& operator-=(Vector2<T>& lhs, const Vector2<T>& rhs) {

    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;

}


template<typename T>
Vector2<T>& operator*=(Vector2<T>& lhs, T rhs) {

    lhs.x *= rhs;
    lhs.y *= rhs;
    return lhs;

}


template<typename T>
Vector2<T>& operator/=(Vector2<T>& lhs, T rhs) {

    lhs.x /= rhs;
    lhs.y /= rhs;
    return lhs;

}


template<typename T>
bool operator==(const Vector2<T>& lhs, const Vector2<T>& rhs) {

    return (lhs.x == rhs.x) && (lhs.y == rhs.y);

}


template<typename T>
bool operator!=(const Vector2<T>& lhs, const Vector2<T>& rhs) {

    return !(lhs == rhs);

}
