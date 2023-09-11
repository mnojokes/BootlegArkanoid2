#pragma once

enum class GameStates
{
    NONE,
    ShowIntro,
    Playing,
    ShowPause,
    ShowGameOver
};

class GameStateManager
{
public:
    bool IsShowingMenu(void) const
    {
        return m_state == GameStates::ShowIntro || m_state == GameStates::ShowPause || m_state == GameStates::ShowGameOver;
    }
    bool IsShowingGame(void) const
    {
        return m_state == GameStates::Playing;
    }
    GameStates GetCurrentState(void) const
    {
        return m_state;
    }

private:
    GameStates m_state = GameStates::NONE;
};
