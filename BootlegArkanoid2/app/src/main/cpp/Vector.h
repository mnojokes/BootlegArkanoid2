#ifndef BOOTLEG_ARKANOID_2_VECTOR_H
#define BOOTLEG_ARKANOID_2_VECTOR_H

class Vector2
{
public:
    Vector2(void);
    Vector2(float x, float y);

    Vector2 operator+(const Vector2& rhs) const;
    Vector2 operator-(const Vector2& rhs) const;
    Vector2 operator-(void) const;
    Vector2 operator*(const Vector2& rhs) const;
    Vector2 operator*(float f) const;
    Vector2& operator+=(const Vector2& rhs);
    Vector2& operator-=(const Vector2& rhs);
    Vector2& operator*=(const Vector2& rhs);
    bool operator==(const Vector2& rhs) const;
    bool operator!=(const Vector2& rhs) const;

    Vector2 Cross(void) const;
    float Dot(const Vector2& rhs) const;

public:
    float x;
    float y;
};

struct Vector3
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

#endif //BOOTLEG_ARKANOID_2_VECTOR_H
