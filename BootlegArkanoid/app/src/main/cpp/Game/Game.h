#pragma once

#include "GameStates.h"
#include "ObjectManager.h"
#include "../Tools/Vector2D.h"
#include "../Tools/FrameCounter.h"
#include "../Graphics/Graphics.h"
#include <thread>
#include <mutex>
#include <vector>
#include <android/native_window.h>

struct InputEvent;

class Game
{
public:
    Game(void);
    ~Game(void);

    bool Initialize(ANativeWindow* window, uint32_t fps);
    void Update(void);
    void Quit(void);

    void RecordInputEvent(const InputEvent& input);

    bool IsInitialized(void) const;

private:
    void ProcessInput(void);

    GameStates LoadNextState(GameStates currentState);

private:
    // Game runtime control variables
    bool m_isInitialized;
    std::thread m_gameLoop; // thread that runs the game loop
    std::mutex m_runLock; // mutex for locking the m_shouldRun variable
    bool m_shouldRun; // controls the main game loop (false == break/terminate)

    // Game "engine" variables
    std::mutex m_dataLock; // mutex for locking internal data that can be accessed from other threads
    std::vector<InputEvent> m_inputEvents;
    GameStates m_state;
    FrameCounter m_frameCounter;
    ObjectManager m_levelManager;
    uint32_t m_currentLevel;
    Graphics m_graphics;

    // Game objects
    std::vector<GameObject>* m_currentlyDisplayed; // points to objects that are currently in play (bricks or menu items)
    std::vector<Brick> m_currentLevelBricks; // stores bricks for current level
    MenuItem m_pauseButton;
    Paddle m_paddle;
    Ball m_ball;

    // Game flow variables
    bool m_currentLevelFinished; // true signals the completion of the current state/level
};
