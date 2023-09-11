#pragma once

enum class InputAction
{
    ActionDown,
    ActionUp,
    ActionMove,
    NONE
};

struct InputEvent
{
    InputAction m_action = InputAction::NONE;
    float x = 0.0f;
    float y = 0.0f;
};
