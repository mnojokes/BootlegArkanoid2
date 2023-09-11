#include <jni.h>

#include "AndroidOut.h"
#include "Game/Game.h"

#include <game-activity/GameActivity.cpp>
#include <game-text-input/gametextinput.cpp>

extern "C"
{

#include <game-activity/native_app_glue/android_native_app_glue.c>

// Implement input event handling function.
static int32_t InputHandler(android_app* app, Game* game) {
    auto ib = android_app_swap_input_buffers(app);
    if (ib && ib->motionEventsCount) {
        for (int i = 0; i < ib->motionEventsCount; i++) {
            InputEvent input;

            auto *event = &ib->motionEvents[i];
            int32_t ptrIdx = 0;
            switch (event->action & AMOTION_EVENT_ACTION_MASK) {
                case AMOTION_EVENT_ACTION_POINTER_DOWN:
                case AMOTION_EVENT_ACTION_POINTER_UP:
                    // Retrieve the index for the starting and the ending of any secondary pointers
                    ptrIdx = (event->action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >>
                                                                                       AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
                case AMOTION_EVENT_ACTION_DOWN:
                    input.m_action = InputAction::ActionDown;
                    break;
                case AMOTION_EVENT_ACTION_UP:
                    input.m_action = InputAction::ActionUp;
                    break;
                case AMOTION_EVENT_ACTION_MOVE:
                    input.m_action = InputAction::ActionMove;
                    // Process the move action: the new coordinates for all active touch pointers
                    // are inside the event->pointers[]. Compare with our internally saved
                    // coordinates to find out which pointers are actually moved. Note that there is
                    // no index embedded inside event->action for AMOTION_EVENT_ACTION_MOVE (there
                    // might be multiple pointers moved at the same time).
                    break;
                default:
                    break;
            }
            input.x = GameActivityPointerAxes_getAxisValue(&event->pointers[ptrIdx], AMOTION_EVENT_AXIS_X);
            input.y = GameActivityPointerAxes_getAxisValue(&event->pointers[ptrIdx], AMOTION_EVENT_AXIS_Y);
            game->ProcessInput(input);
        }
        android_app_clear_motion_events(ib);
    }
    return 0;
}

void handle_cmd(android_app *app, int32_t cmd)
{
    switch (cmd)
    {
        case APP_CMD_INIT_WINDOW:
        {
            Game* game = new Game();
            game->Initialize(app);
            app->userData = game;
        }
            break;
        case APP_CMD_TERM_WINDOW:
            if (app->userData)
            {
                Game* game = reinterpret_cast<Game*>(app->userData);
                game->Exit();

                app->userData = nullptr;
                delete game;
            }
            break;
        default:
            break;
    }
}

/*!
 * This the main entry point for a native activity
 */
void android_main(struct android_app *pApp)
{
    // Register an event handler for Android events
    pApp->onAppCmd = handle_cmd;
    android_app_set_motion_event_filter(pApp, nullptr);

    // This sets up a typical game/event loop. It will run until the app is destroyed.
    int events;
    android_poll_source *pSource;
    do {
        // Process all pending events before running game logic.
        if (ALooper_pollAll(0, nullptr, &events, (void **) &pSource) >= 0)
        {
            if (pSource)
            {
                pSource->process(pApp, pSource);
            }
        }

        if (pApp->userData)
        {
            Game* game = reinterpret_cast<Game*>(pApp->userData);
            game->StartFrame();
            InputHandler(pApp, game);
            game->UpdateObjects();
            game->RenderFrame();
            game->EndFrame();
        }
    } while (!pApp->destroyRequested);
}
}
