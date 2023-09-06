#include "Game.h"

Game::Game(void)
    : m_isRunning(false)
{}

bool Game::Initialize(void)
{
    m_isRunning = true;
    return m_isRunning;
}
