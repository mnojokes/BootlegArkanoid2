#ifndef BOOTLEG_ARKANOID_2_COLLIDER_H
#define BOOTLEG_ARKANOID_2_COLLIDER_H

#include "../Vector.h"

class Collider
{
public:
    // TODO: create collision checking functions

    static bool IsPointInQuad(const Vector2& point, const Vector2& quadCenter, const Vector2& halfExtents);
};

#endif //BOOTLEG_ARKANOID_2_COLLIDER_H
