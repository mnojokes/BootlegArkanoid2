#include "Collider.h"
#include <limits>

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

Vector2 Collider::ProcessBallMovement(Ball& ball, const Paddle& paddle, std::vector<Brick>& bricks, float deltaTime) const
{
    Vector2 oldPos = ball.m_render.GetPosition();

    Vector2 newPos = oldPos;
    newPos.x += ball.m_velocity.x * (1.0f - deltaTime);
    newPos.y += ball.m_velocity.y * (1.0f - deltaTime);

    struct Collision
    {
        Intersection m_intersect;
        Vector2 m_pointA;
        Vector2 m_pointB;
        Vector2 m_normal;
    };

    Vector2 ballDirection = ball.m_velocity.Normalize();
    std::vector<Collision> collisions;

    /*

    Intersection it = CircleLineCollision(ball.m_render.GetPosition(), ballDirection, ball.m_radius, m_boundaryTopLeft, m_boundaryTopRight);
    Intersection ir = CircleLineCollision(ball.m_render.GetPosition(), ballDirection, ball.m_radius, m_boundaryTopRight, m_boundaryBottomRight);
    Intersection ib = CircleLineCollision(ball.m_render.GetPosition(), ballDirection, ball.m_radius, m_boundaryBottomRight, m_boundaryBottomLeft);
    Intersection il = CircleLineCollision(ball.m_render.GetPosition(), ballDirection, ball.m_radius, m_boundaryTopLeft, m_boundaryBottomLeft);

    if (it.m_time > 0.0f)
    {
        Collision col;
        col.m_intersect = it;
        col.m_pointA = m_boundaryTopLeft;
        col.m_pointB = m_boundaryTopRight;
        col.m_normal = { 0, 1 };
        collisions.push_back(col);
    }
    if (i1.m_time > 0.0f)
    {
        Collision col;
        col.m_intersect = i1;
        col.m_pointA = m_boundaryTopRight; m_boundaryBottomRight
        col.m_pointB = c;
        col.m_normal = { 1, 0 };
        collisions.push_back(col);
    }
    if (i2.m_time > 0.0f)
    {
        Collision col;
        col.m_intersect = i2;
        col.m_pointA = c;
        col.m_pointB = d;
        col.m_normal = { 0, -1 };
        collisions.push_back(col);

    }
    if (i3.m_time > 0.0f)
    {
        Collision col;
        col.m_intersect = i3;
        col.m_pointA = d;
        col.m_pointB = a;
        col.m_normal = { -1, 0 };
        collisions.push_back(col);
    }

     */

    for (auto& brick : bricks)
    {
        Vector2 pos = brick.m_render.GetPosition();
        Vector2 a = { pos.x - brick.m_halfExtents.x, pos.y + brick.m_halfExtents.y };
        Vector2 b = { pos.x + brick.m_halfExtents.x, pos.y + brick.m_halfExtents.y };
        Vector2 c = { pos.x + brick.m_halfExtents.x, pos.y - brick.m_halfExtents.y };
        Vector2 d = { pos.x - brick.m_halfExtents.x, pos.y - brick.m_halfExtents.y };

        Intersection i0 = CircleLineCollision(ball.m_render.GetPosition(), ballDirection, ball.m_radius, a, b);
        Intersection i1 = CircleLineCollision(ball.m_render.GetPosition(), ballDirection, ball.m_radius, b, c);
        Intersection i2 = CircleLineCollision(ball.m_render.GetPosition(), ballDirection, ball.m_radius, c, d);
        Intersection i3 = CircleLineCollision(ball.m_render.GetPosition(), ballDirection, ball.m_radius, d, a);

        if (i0.m_time > 0.0f)
        {
            Collision col;
            col.m_intersect = i0;
            col.m_pointA = a;
            col.m_pointB = b;
            col.m_normal = { 0, 1 };
            collisions.push_back(col);
        }
        if (i1.m_time > 0.0f)
        {
            Collision col;
            col.m_intersect = i1;
            col.m_pointA = b;
            col.m_pointB = c;
            col.m_normal = { 1, 0 };
            collisions.push_back(col);
        }
        if (i2.m_time > 0.0f)
        {
            Collision col;
            col.m_intersect = i2;
            col.m_pointA = c;
            col.m_pointB = d;
            col.m_normal = { 0, -1 };
            collisions.push_back(col);

        }
        if (i3.m_time > 0.0f)
        {
            Collision col;
            col.m_intersect = i3;
            col.m_pointA = d;
            col.m_pointB = a;
            col.m_normal = { -1, 0 };
            collisions.push_back(col);
        }

    }

    std::sort(collisions.begin(), collisions.end(), [](const Collision& a, const Collision& b) { return a.m_intersect.m_time < b.m_intersect.m_time; });
    if (!collisions.empty())
    {
        printf("something");
    }

    std::vector<Collision> deepestCollisions;
    float min = std::numeric_limits<float>::max();
    for (Collision& col : collisions)
    {
        if (col.m_intersect.m_time - min <= 1e-06f)
        {
            deepestCollisions.push_back(col);
            min = col.m_intersect.m_time;
        }
        else
        {
            break;
        }
    }

    Vector2 collisionNormal;
    Vector2 collisionPosition;
    if (!deepestCollisions.empty())
    {
        for (const Collision& col : deepestCollisions)
        {
            collisionNormal += col.m_normal;
            collisionPosition += col.m_intersect.m_point;
        }
        collisionNormal = collisionNormal.Normalize();
        collisionPosition.x /= deepestCollisions.size();
        collisionPosition.y /= deepestCollisions.size();
    }
    else
    {
        return newPos;
    }

    Vector2 vecCollisionPosition = collisionPosition - newPos;
    Vector2 directionToCollision = vecCollisionPosition.Normalize();
    float collisionPositionMag = 0.0f;
    float totalPathMag = (newPos - oldPos).Magnitude();
    float diroCol = directionToCollision.Dot(ballDirection);

    float tc = 0.0f;
    if (diroCol + 1e-06f > 1.0f)
    {
        collisionPositionMag = vecCollisionPosition.Magnitude();
        float offset = ball.m_radius - collisionPositionMag;
        float requiredDistance = totalPathMag - offset;
        if (totalPathMag > 0.0f)
        {
            tc = requiredDistance / totalPathMag;
        }
    }
    else
    {
        Vector2 pointOnDirection;
        Vector2 normalizeVecCollisionPosition = vecCollisionPosition.Normalize();
        float collPosoDir = normalizeVecCollisionPosition.Dot(ballDirection);
        if (collPosoDir + 1e-06f > 1.0f)
        {
            // TODO
        }
        else
        {
            pointOnDirection = newPos + ballDirection * deepestCollisions[0].m_intersect.m_time;
        }
        vecCollisionPosition = pointOnDirection - newPos;
        collisionPositionMag = vecCollisionPosition.Magnitude();
        float offset = ball.m_radius - collisionPositionMag;
        float requiredDistance = totalPathMag - offset;
        if (totalPathMag > 0.0f)
        {
            tc = requiredDistance / totalPathMag;
        }
    }

    newPos = oldPos;

    newPos.x += ball.m_velocity.x * (1.0f - deltaTime) * tc * 0.5f;
    newPos.y += ball.m_velocity.y * (1.0f - deltaTime) * tc * 0.5f;

    if (deepestCollisions[0].m_normal.x != 0.0f)
    {
        ball.m_velocity.y = -ball.m_velocity.y;
    }
    if (deepestCollisions[0].m_normal.y != 0.0f)
    {
        ball.m_velocity.x = -ball.m_velocity.x;
    }

    ball.m_velocity.x = -ball.m_velocity.x;
    ball.m_velocity.y = -ball.m_velocity.y;

    newPos.y += ball.m_velocity.y * (1.0f - deltaTime);
    newPos.x += ball.m_velocity.x * (1.0f - deltaTime);

    if (!deepestCollisions.empty())
    {
        printf("something");
    }


    /*
    pos.x += m_ball.m_velocity.x * (1.0f - m_frameCounter.GetDelta());
    pos.y += m_ball.m_velocity.y * (1.0f - m_frameCounter.GetDelta());
     */
    // TODO: handle collisions with boundaries and other objects


    return newPos;
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

Intersection Collider::CircleLineCollision(const Vector2& position, const Vector2& direction, float radius, const Vector2& a, const Vector2& b) const
{
    Vector2 ab = b - a;
    Vector2 ba = a - b;
    Vector2 ac = position - a;
    Vector2 bc = position - b;

    float ABoAC = ab.Dot(ac);
    float BAoBC = ba.Dot(bc);

    Vector2 closestPointOnLine
    {
        std::numeric_limits<float>::min(),
        std::numeric_limits<float>::min()
    };
    float distance = 0.0f;
    if (ABoAC > 0.0f && BAoBC > 0.0f)
    {
        float area = fabs(ab.x * ac.y - ab.y * ac.x);
        distance =  area / ab.Magnitude();
    }
    else
    {
        float magAC = ac.Magnitude();
        float magBC = bc.Magnitude();
        if (magAC < magBC)
        {
            distance = magAC;
            closestPointOnLine = a;
        }
        else
        {
            distance = magBC;
            closestPointOnLine = b;
        }
    }

    if (distance > radius)
    { // no collision
        return {};
    }

    if (closestPointOnLine.x == std::numeric_limits<float>::min() &&
    closestPointOnLine.y == std::numeric_limits<float>::min())
    {
        Vector2 abCross = { ab.y, -ab.x };
        Vector2 lineNormal = abCross.Normalize();

        float ABXoAC = abCross.Dot(ac);
        if (ABXoAC > 0.0f)
        {
            lineNormal = -lineNormal;
        }

        closestPointOnLine = position + lineNormal * distance;
    }

    Vector2 vecToClosestPointOnLine = closestPointOnLine - position;
    Vector2 normalizedVecClosestPointOnLine = vecToClosestPointOnLine.Normalize();
    float angleBetweenVecClosestPointOnLineAndFlippedDirection = normalizedVecClosestPointOnLine.Dot(direction);
    if (angleBetweenVecClosestPointOnLineAndFlippedDirection + 1e-06 > 1.0f)
    {
        Intersection ret;
        ret.m_time = distance;
        ret.m_point = position + direction * distance;
        return ret;
    }

    float magnitudeToCollision = sqrt(radius * radius - distance * distance);
    if (magnitudeToCollision < 1e-06f)
    { // degenerate triangle
        Intersection ret;
        ret.m_time = distance;
        ret.m_point = closestPointOnLine;
        return ret;
    }

    Vector2 collisionCross = { vecToClosestPointOnLine.y, -vecToClosestPointOnLine.x };
    collisionCross = collisionCross.Normalize();

    Vector2 pointOnArc = closestPointOnLine + collisionCross * magnitudeToCollision;

    collisionCross = { vecToClosestPointOnLine.y, vecToClosestPointOnLine.x };
    collisionCross = collisionCross.Normalize();

    Vector2 pointOnArc2 = closestPointOnLine + collisionCross * magnitudeToCollision;

    float distPointOnArc = (pointOnArc - position).Magnitude();
    float distPointOnArc2 = (pointOnArc2 - position).Magnitude();

    Intersection ret;
    ret.m_time = distance;
    ret.m_point = distPointOnArc > distPointOnArc2 ? pointOnArc : pointOnArc2;
    return ret;
}
