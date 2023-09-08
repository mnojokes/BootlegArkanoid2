#include "Game.h"
#include "InputEvent.h"

namespace
{
    constexpr int minimumAllowedResolutionPixels = 480;
    constexpr size_t inputEventBufferSize = 5;
}


Game::Game()
    : m_isInitialized(false)
    , m_shouldRun(false)
    , m_state(GameStates::ShowIntro)
    , m_currentLevel(0)
{
    m_inputEvents.reserve(inputEventBufferSize);
}

Game::~Game()
{
    if (m_isInitialized) { Quit(); }
}

bool Game::Initialize(Vec2D<int> resolution, uint32_t fps)
{
    m_resolution = resolution;
    if (resolution.x < minimumAllowedResolutionPixels || resolution.y < minimumAllowedResolutionPixels)
    {
        // TODO: log illegal resolution
        return false;
    }

    m_frameCounter.SetFPSLock(fps);

    m_isInitialized = m_shouldRun = true;
    m_gameLoop = std::thread([this]() { Update(); });
    return m_isInitialized;
}

void Game::Update()
{
    while(true)
    {
        m_frameCounter.Start();
        m_runLock.lock();
        if (!m_shouldRun) { m_runLock.unlock(); break; }
        m_runLock.unlock();

        ProcessInput();
        // TODO: implement game loop logic here
        m_frameCounter.Stop();
    }
}

void Game::Quit()
{
    m_runLock.lock();
    m_shouldRun = false;
    m_runLock.unlock();

    m_gameLoop.join();

    m_resolution = { 0, 0};
    m_state = GameStates::ShowIntro;
    // TODO: return everything to uninitialized state
    m_isInitialized = false;
}

void Game::RecordInputEvent(const InputEvent& input)
{
    std::scoped_lock lock(m_dataLock);
    m_inputEvents.push_back(input);
}

bool Game::IsInitialized() const
{
    return m_isInitialized;
}

void Game::ProcessInput()
{
    std::scoped_lock lock(m_dataLock);
    for (InputEvent& event : m_inputEvents)
    {
        // TODO: process input event
        switch (m_state)
        {
            case GameStates::Playing:
                // check for taps on pause button
                // check for taps and moves on the paddle
                break;
            case GameStates::ShowIntro:
            case GameStates::ShowPause:
            case GameStates::ShowGameOver:
                // check for taps on menu items
                break;
        }
    }
    m_inputEvents.clear();
}
