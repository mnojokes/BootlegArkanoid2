#pragma once

#include "GameStates.h"
#include "ObjectManager.h"
#include "../Tools/Vector2D.h"
#include "../Tools/FrameCounter.h"
#include <thread>
#include <mutex>
#include <vector>

struct InputEvent;

class Game
{
public:
    Game(void);
    ~Game(void);

    bool Initialize(Vec2D<int> resolution, uint32_t fps);
    void Update(void);
    void Quit(void);

    void RecordInputEvent(const InputEvent& input);

    bool IsInitialized(void) const;

private:
    void ProcessInput(void);

private:
    Vec2D<int> m_resolution;
    bool m_isInitialized;
    std::mutex m_runLock;
    std::thread m_gameLoop;
    bool m_shouldRun;

    std::mutex m_dataLock;
    std::vector<InputEvent> m_inputEvents;
    GameStates m_state;

    FrameCounter m_frameCounter;
    ObjectManager m_levelManager;
    uint32_t m_currentLevel;
};
