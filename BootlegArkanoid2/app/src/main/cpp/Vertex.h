#ifndef BOOTLEG_ARKANOID_2_VERTEX_H
#define BOOTLEG_ARKANOID_2_VERTEX_H

#include "Vector.h"

struct Vertex
{
    Vertex(const Vector3& position, const Vector2& uv)
            : m_position(position)
            , m_uv(uv)
    {}

    Vector3 m_position;
    Vector2 m_uv;
};

#endif //BOOTLEG_ARKANOID_2_VERTEX_H
