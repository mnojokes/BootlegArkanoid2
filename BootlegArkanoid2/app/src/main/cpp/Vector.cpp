#include "Vector.h"

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

Vector2 Vector2::Cross() const
{
    return { -y, x};
}

float Vector2::Dot(const Vector2& rhs) const
{
    return (x * rhs.x) + (y * rhs.y);
}
