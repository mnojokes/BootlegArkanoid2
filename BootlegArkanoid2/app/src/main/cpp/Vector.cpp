#include "Vector.h"
#include <cmath>

Vector2::Vector2()
        : x(0.0f)
        , y(0.0f)
{}

Vector2::Vector2(float x, float y)
        : x(x)
        , y(y)
{}

Vector2 Vector2::operator+(const Vector2& rhs) const
{
    return { x + rhs.x, y + rhs.y };
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
    return { x - rhs.x, y - rhs.y };
}

Vector2 Vector2::operator-() const
{
    return { -x, -y };
}

Vector2 Vector2::operator*(const Vector2& rhs) const
{
    return { x * rhs.x, y * rhs.y };
}

Vector2 Vector2::operator*(float f) const
{
    return { x * f, y * f };
}

Vector2 operator*(float f, const Vector2& lhs)
{
    return { f * lhs.x, f * lhs.y };
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
    *this = *this + rhs;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
    *this = *this - rhs;
    return *this;
}

Vector2& Vector2::operator*=(const Vector2& rhs)
{
    *this = *this * rhs;
    return *this;
}

bool Vector2::operator==(const Vector2& rhs) const
{
    return x == rhs.x && y == rhs.y;
}

bool Vector2::operator!=(const Vector2& rhs) const
{
    return !(*this == rhs);
}

float Vector2::Dot(const Vector2& rhs) const
{
    return (x * rhs.x) + (y * rhs.y);
}

float Vector2::Magnitude(void) const
{
    float magSq = (x * x) + (y * y);
    return sqrt(magSq);
}

float Vector2::MagnitudeSq(void) const
{
    return (x * x) + (y * y);
}

Vector2 Vector2::Normalize(void) const
{
    Vector2 v;

    float mag = Magnitude();
    if (mag != 0.0f)
    {
        v.x = x / mag;
        v.y = y / mag;
    }

    return v;
}
