#pragma once

template <typename NumType>
struct Vec2D
{
    Vec2D(void) : x(0), y(0) {}
    Vec2D(NumType x, NumType y) : x(x), y(y) {}

    NumType x;
    NumType y;
};
