#pragma once

#include "Vector2D.h"
#include "GameStates.h"

class Game
{
public:
    Game(void);
    ~Game(void);

    bool Initialize(Vec2D<int> resolution);
    void Update(void);
    void Quit(void);

    bool IsInitialized(void) const;

private:
    Vec2D<int> m_resolution;
    bool m_isInitialized;

    bool m_shouldRun;
    GameStates m_state;
};
