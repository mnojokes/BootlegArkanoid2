#ifndef BOOTLEG_ARKANOID_2_GAME_H
#define BOOTLEG_ARKANOID_2_GAME_H

#include "InputEvent.h"
#include "GameStates.h"
#include "ObjectManager.h"
#include "Collider.h"
#include "../Vector.h"
#include "FrameCounter.h"
#include <thread>
#include <mutex>
#include <vector>

class Game
{
public:
    Game(void);
    ~Game(void);

    bool Initialize(struct android_app* app);

    void StartFrame(void);
    void EndFrame(void);

    void UpdateObjects(void);
    void RenderFrame(void);

    void Exit(void);

    void ProcessInput(const InputEvent& input);
    bool IsInitialized(void) const;

private:
    // Game runtime control variables
    bool m_isInitialized = false;
    bool m_shouldRun = false; // controls the main game loop (false == break/terminate)

    // Game "engine" variables
    bool m_isStateChanged = true;
    Vector2 m_displaySize;
    Vector2 m_displayCenterTouch;
    GameStateManager m_state;
    FrameCounter m_frameCounter;
    ObjectManager m_objectManager;
    uint32_t m_currentLevel = 0;
    Collider m_collider;
    class Renderer* m_renderer;


    // Game objects
    std::vector<const MenuItem*> m_menuItems; // menu items currently visible
    std::vector<Brick> m_currentLevelBricks; // bricks in current level
    Paddle m_paddle;
    Ball m_ball;

    // Game flow variables
    bool m_isPaddlePressed = false; // input variable: true if player is touching the paddle
};

#endif //BOOTLEG_ARKANOID_2_GAME_H
