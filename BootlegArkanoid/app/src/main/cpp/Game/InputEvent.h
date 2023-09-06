#pragma once

enum class InputAction
{
    ActionDown,
    ActionUp,
    ActionMove
};

struct InputEvent
{
    explicit InputEvent(InputAction action, float x, float y)
        : m_action(action)
        , m_coordX(x)
        , m_coordY(y)
    {}

    InputAction m_action;
    float m_coordX;
    float m_coordY;
};
