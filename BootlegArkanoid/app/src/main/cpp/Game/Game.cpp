#include "Game.h"

constexpr int minimumAllowedResolutionPixels = 480;

Game::Game()
    : m_isInitialized(false)
    , m_shouldRun(false)
    , m_state(GameStates::Paused)
{}

Game::~Game()
{
    if (m_isInitialized) { Quit(); }
}

bool Game::Initialize(Vec2D<int> resolution)
{
    m_resolution = resolution;

    if (resolution.x < minimumAllowedResolutionPixels || resolution.y < minimumAllowedResolutionPixels)
    {
        // TODO: log illegal resolution
        return false;
    }

    m_isInitialized = m_shouldRun = true;
    return m_isInitialized;
}

void Game::Update()
{

}

void Game::Quit()
{
    m_shouldRun = false;
    m_resolution = { 0, 0};

    m_state = GameStates::Paused;
    // TODO: return everything to uninitialized state

    m_isInitialized = false;
}

bool Game::IsInitialized() const
{
    return m_isInitialized;
}
