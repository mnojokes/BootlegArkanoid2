#pragma once

#include "InputEvent.h"

class GameControl
{
public:
    static bool Start(void);

    static bool NewInputEvent(int action, float x, float y);
};
