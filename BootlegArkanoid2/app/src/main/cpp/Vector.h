#ifndef BOOTLEG_ARKANOID_2_VECTOR_H
#define BOOTLEG_ARKANOID_2_VECTOR_H

struct Vector2
{
    Vector2 operator*(float scalar) const
    {
        return { x * scalar, y * scalar };
    }

    float x = 0.0f;
    float y = 0.0f;
};

struct Vector3
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

#endif //BOOTLEG_ARKANOID_2_VECTOR_H
