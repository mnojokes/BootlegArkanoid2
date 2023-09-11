#include "Game.h"
#include "../Renderer.h"
#include "../RenderObject.h"
#include <vector>
#include <game-activity/native_app_glue/android_native_app_glue.h>

Game::Game()
    : m_isInitialized(false)
    , m_renderer(nullptr)
    , m_shouldRun(false)
    , m_isStateChanged(true)
    , m_currentLevel(0)
    , m_isPaddlePressed(false)
    , m_objectManager({ 1080, 2220 }) // TODO: change later to extract resolution from window
    , m_currentlyDisplayed(nullptr)
{}

Game::~Game()
{
    if (m_isInitialized)
    {
        Exit();
    }
}

bool Game::Initialize(android_app* app)
{
    if (app == nullptr) { return false; }
    m_renderer = new Renderer(app);
    if (!m_renderer->Initialize())
    {
        return false;
    }



    m_isInitialized = true;
    return m_isInitialized;
}

void Game::StartFrame()
{
    m_frameCounter.Start();
}
void Game::EndFrame()
{
    m_frameCounter.Stop();
}

void Game::UpdateObjects()
{
    // TODO: update object positions, states
}

void Game::RenderFrame()
{
    static RenderObject ro("android_robot.png");
    std::vector<const RenderObject*> v;
    v.push_back(&ro);
    m_renderer->Render(v);
}

void Game::Exit()
{
    // TODO
    m_isInitialized = false;
}

bool Game::IsInitialized() const
{
    return m_isInitialized;
}

void Game::ProcessInput(const InputEvent& input)
{
    // Current input reacts immediately upon touch.
    // TODO: consider changing the input logic to register both down position and up position to make selection of menu items more consistent with general Android UI
    if (m_state.IsShowingGame())
    {
        if (m_isPaddlePressed)
        {
            switch (input.m_action)
            {
                case InputAction::ActionMove:
                    // TODO: move paddle
                    break;
                case InputAction::ActionUp:
                    // TODO: release paddle
                    break;
                case InputAction::ActionDown:
                    // TODO: if menu item pressed, release paddle, switch context;
                    break;
            }
        }
        else
        {
            switch (input.m_action)
            {
                case InputAction::ActionDown:
                    // TODO: only handle touches on paddle or menu items
                    break;
                default:
                    // reject other actions, only paddle and menu item touches matter at this point
                    break;
            }
        }
    }
    else if (m_state.IsShowingMenu())
    {
        switch (input.m_action)
        {
            case InputAction::ActionDown:

                break;
            default:
                break;
        }
    }
}

std::vector<GameObject>* Game::LoadObjectsForNewState(GameStates newState)
{
    if (newState == GameStates::Playing)
    {
        if (!m_currentLevelBricks.empty())
        {
            return &m_currentLevelBricks;
        }
        else if (m_currentLevel <= m_objectManager.GetNumberOfLevels())
        {
            m_objectManager.GetDefaults(m_currentLevelBricks, m_currentLevel);
            return &m_currentLevelBricks;
        }

        newState = GameStates::ShowGameOver;
    }

    return nullptr;
    // TODO: load menu items here
}


