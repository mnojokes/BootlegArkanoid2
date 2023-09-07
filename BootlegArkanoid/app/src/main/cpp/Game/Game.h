#pragma once

#include "GameStates.h"
#include "../Tools/Vector2D.h"
#include "../Tools/FrameCounter.h"

class Game
{
public:
    Game(void);
    ~Game(void);

    bool Initialize(Vec2D<int> resolution, uint32_t fps);
    void Update(void);
    void Quit(void);

    bool IsInitialized(void) const;

private:
    Vec2D<int> m_resolution;
    bool m_isInitialized;

    bool m_shouldRun;
    GameStates m_state;

    FrameCounter m_frameCounter;
};
