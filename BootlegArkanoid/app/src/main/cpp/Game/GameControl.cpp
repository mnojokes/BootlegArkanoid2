#include "GameControl.h"
#include "Game.h"
#include "InputEvent.h"

namespace
{
    Game g_gameInstance;
}

bool GameControl::Initialize(int sizeX, int sizeY)
{
    return g_gameInstance.Initialize(Vec2D(sizeX, sizeY));
}

void GameControl::Run()
{
    if (!g_gameInstance.IsInitialized())
    {
        // TODO: log uninitialized game state
        return;
    }

    g_gameInstance.Update();
}

void GameControl::Exit()
{
    if (g_gameInstance.IsInitialized())
    {
        g_gameInstance.Quit();
    }
}

bool GameControl::NewInputEvent(int action, float x, float y)
{
    InputAction inputAction;
    switch (action)
    {
        case 0: // https://developer.android.com/reference/android/view/MotionEvent#ACTION_DOWN
            inputAction = InputAction::ActionDown;
            break;
        case 1: // https://developer.android.com/reference/android/view/MotionEvent#ACTION_UP
            inputAction = InputAction::ActionUp;
            break;
        case 2: // https://developer.android.com/reference/android/view/MotionEvent#ACTION_MOVE
            inputAction = InputAction::ActionMove;
            break;
        default:
            // TODO: log invalid input action received
            return false;
    }

    InputEvent input = InputEvent(inputAction, x, y);

    return true;
}
