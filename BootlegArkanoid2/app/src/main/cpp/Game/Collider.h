#ifndef BOOTLEG_ARKANOID_2_COLLIDER_H
#define BOOTLEG_ARKANOID_2_COLLIDER_H

#include "../Vector.h"
#include "GameObjects.h"
#include <vector>

struct Intersection
{
    float m_time = -1.0f; // no collision
    Vector2 m_point;
};

class Collider
{
public:
    // Initialize: set max values for X and Y axes which will be used as boundaries for game object movement
    void Initialize(const Vector2& boundaries);

    static bool IsPointInQuad(const Vector2& point, const Vector2& quadCenter, const Vector2& halfExtents);

    // ProcessBallMovement: returns new ball position considering its velocity and collisions with objects and boundaries
    Vector2 ProcessBallMovement(Ball& ball, const Paddle& paddle, std::vector<Brick>& bricks, float deltaTime) const;

    // ProcessPaddleMovement: returns new paddle position considering its collisions with game space boundaries
    // Paddle moves only on the X axis
    Vector2 ProcessPaddleMovementX(const Paddle& paddle, const Vector2& position) const;

private:
    Intersection CircleLineCollision(const Vector2& position, const Vector2& direction, float radius, const Vector2& a, const Vector2& b) const;

private:
    Vector2 m_boundaryTopLeft;
    Vector2 m_boundaryTopRight;
    Vector2 m_boundaryBottomLeft;
    Vector2 m_boundaryBottomRight;
};

#endif //BOOTLEG_ARKANOID_2_COLLIDER_H
