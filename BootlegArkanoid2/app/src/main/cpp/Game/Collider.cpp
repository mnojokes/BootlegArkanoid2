#include "Collider.h"

void Collider::Initialize(const Vector2& boundaries)
{
    m_boundaryTopLeft.x = m_boundaryBottomLeft.x = -boundaries.x;
    m_boundaryTopRight.x = m_boundaryBottomRight.x = boundaries.x;
    m_boundaryTopLeft.y = m_boundaryTopRight.y = boundaries.y;
    m_boundaryBottomLeft.y = m_boundaryBottomRight.y = -boundaries.y;
}

bool Collider::IsPointInQuad(const Vector2 &point, const Vector2 &quadCenter, const Vector2 &halfExtents)
{
    return (point.x >= quadCenter.x - halfExtents.x
            && point.x <= quadCenter.x + halfExtents.x
            && point.y >= quadCenter.y - halfExtents.y
            && point.y <= quadCenter.y + halfExtents.y);
}

Vector2 Collider::ProcessBallMovement(const Ball& ball, std::vector<Brick>& bricks, float deltaTime) const
{
    Vector2 pos = ball.m_render.GetPosition();


    /*
    pos.x += m_ball.m_velocity.x * (1.0f - m_frameCounter.GetDelta());
    pos.y += m_ball.m_velocity.y * (1.0f - m_frameCounter.GetDelta());
     */
    // TODO: handle collisions with boundaries and other objects


    return pos;
}

Vector2 Collider::ProcessPaddleMovementX(const Paddle& paddle, const Vector2& position) const
{
    Vector2 newPos = paddle.m_render.GetPosition();
    newPos.x = position.x;
    if (newPos.x - paddle.m_halfExtents.x < m_boundaryTopLeft.x)
    {
        newPos.x = m_boundaryTopLeft.x + paddle.m_halfExtents.x;
    }
    else if (newPos.x + paddle.m_halfExtents.x > m_boundaryTopRight.x)
    {
        newPos.x = m_boundaryTopRight.x - paddle.m_halfExtents.x;
    }

    return newPos;
}

void Collider::CircleLineCollision(const Vector2& position, float radius, const Vector2& a, const Vector2& b)
{
    Vector2 ab = b - a;
    Vector2 ba = a - b;
    Vector2 ac = position - a;
    Vector2 bc = position - b;

    float dotAC = ab.Dot(ac);
    float dotBC = ab.Dot(bc);

    if (dotAC < 0.0f)
    { // Position not within line, calculate relative to A

    }
    else if (dotBC < 0.0f)
    { // Position not within line, calculate relative to B

    }
    else
    { // Position within line

    }
}
