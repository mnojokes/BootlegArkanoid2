#pragma once

#include <android/native_window.h>

class GameControl
{
public:
    static bool Initialize(ANativeWindow* window, float fps);
    static void Exit(void);

    static bool NewInputEvent(int action, float x, float y);
};
