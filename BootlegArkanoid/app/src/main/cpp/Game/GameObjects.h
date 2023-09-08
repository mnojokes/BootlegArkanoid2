#pragma once

#include "../Tools/Vector2D.h"

class Brick
{
public:
    Vec2D<float> m_position;
    Vec2D<float> m_halfExtents;
    int m_lives = 0;
};

class Paddle
{
public:
    Vec2D<float> m_position;
    Vec2D<float> m_halfExtents;
};

class Ball
{
public:
    Vec2D<float> m_position;
    Vec2D<float> m_velocity;
    float m_radius;
};
