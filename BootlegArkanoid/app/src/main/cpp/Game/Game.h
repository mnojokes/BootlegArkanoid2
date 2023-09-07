#pragma once

#include "GameStates.h"
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
    std::thread m_gameLoop;
    std::mutex m_runLock;
    bool m_shouldRun;

    std::mutex m_dataLock;
    std::vector<InputEvent> m_inputEvents;
    GameStates m_state;

    FrameCounter m_frameCounter;
};
