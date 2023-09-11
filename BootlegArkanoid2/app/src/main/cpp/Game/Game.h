#ifndef BOOTLEG_ARKANOID_2_GAME_H
#define BOOTLEG_ARKANOID_2_GAME_H

#include "InputEvent.h"
#include "GameStates.h"
#include "ObjectManager.h"
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
    std::vector<GameObject>* LoadObjectsForNewState(GameStates newState);

private:
    // Game runtime control variables
    bool m_isInitialized;
    bool m_shouldRun; // controls the main game loop (false == break/terminate)

    // Game "engine" variables
    bool m_isStateChanged;
    GameStateManager m_state;
    FrameCounter m_frameCounter;
    ObjectManager m_objectManager;
    uint32_t m_currentLevel;
    class Renderer* m_renderer;

    // Game objects
    std::vector<GameObject>* m_currentlyDisplayed; // points to objects that are currently in play (bricks or menu items)
    std::vector<GameObject> m_currentLevelBricks; // stores bricks for current level
    MenuItem m_pauseButton;
    Paddle m_paddle;
    Ball m_ball;

    // Game flow variables
    bool m_isPaddlePressed; // input variable: true if player is touching the paddle
};

#endif //BOOTLEG_ARKANOID_2_GAME_H
