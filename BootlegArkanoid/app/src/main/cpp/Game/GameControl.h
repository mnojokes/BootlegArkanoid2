#pragma once

class GameControl
{
public:
    static bool Initialize(int sizeX, int sizeY);
    static void Run(void);
    static void Exit(void);

    static bool NewInputEvent(int action, float x, float y);
};
