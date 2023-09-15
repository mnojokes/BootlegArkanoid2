#pragma once

enum class GameStates
{
    NONE,
    ShowIntro,
    Playing,
    ShowPause,
    ShowGameOver,
    Quit
};

class GameStateManager
{
public:
    bool IsShowingMenu(void) const
    {
        return m_state != GameStates::Playing;
    }
    bool IsShowingGame(void) const
    {
        return m_state == GameStates::Playing;
    }
    GameStates GetCurrentState(void) const
    {
        return m_state;
    }
    void SetCurrentState(GameStates state)
    {
        m_state = state;
    }

private:
    GameStates m_state = GameStates::NONE;
};
