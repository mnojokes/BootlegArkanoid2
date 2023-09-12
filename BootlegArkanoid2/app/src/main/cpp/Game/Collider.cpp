#include "Collider.h"

bool Collider::IsPointInQuad(const Vector2 &point, const Vector2 &quadCenter, const Vector2 &halfExtents)
{
    return (point.x >= quadCenter.x - halfExtents.x
            && point.x <= quadCenter.x + halfExtents.x
            && point.y >= quadCenter.y - halfExtents.y
            && point.y <= quadCenter.y + halfExtents.y);
}
