#include "Game.h"
#include "../Renderer.h"
#include "../RenderObject.h"
#include <vector>
#include <game-activity/native_app_glue/android_native_app_glue.h>
#include "../Utility.h"

Game::Game()
    : m_renderer(nullptr)
    , m_paddle("")
    , m_ball("")
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

    m_displaySize.x = static_cast<float>(ANativeWindow_getWidth(app->window));
    m_displaySize.y = static_cast<float>(ANativeWindow_getHeight(app->window));
    m_objectManager.Initialize(m_displaySize);
    m_displayCenter.x = m_displaySize.x * 0.5f;
    m_displayCenter.y = m_displaySize.y * 0.5f;

    m_paddle = m_objectManager.GetDefaultPaddle();
    m_ball = m_objectManager.GetDefaultBall();

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
    if (m_currentLevelBricks.empty())
    {
        m_objectManager.LoadLevelBricks(m_currentLevelBricks, m_currentLevel);
        ++m_currentLevel;
    }
    if (m_isStateChanged)
    {
        m_objectManager.LoadMenuObjects(m_menuItems, m_state.GetCurrentState());
        m_isStateChanged = false;
    }

    Vector2 pos = m_ball.m_render.GetPosition();
    pos.x += m_ball.m_velocity.x * (1.0f - m_frameCounter.GetDelta());
    pos.y += m_ball.m_velocity.y * (1.0f - m_frameCounter.GetDelta());
    // TODO: handle collisions with boundaries and other objects
    m_ball.m_render.SetPosition(pos);
}

void Game::RenderFrame()
{
    std::vector<const RenderObject*> v;
    for (const Brick& br : m_currentLevelBricks)
    {
        // TODO: check if visible, render only visible objects
        v.push_back(&br.m_render);
    }

    v.push_back(&m_paddle.m_render);
    v.push_back(&m_ball.m_render);

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
    Vector2 coords; // coordinates adjusted to match game world's cartesian space
    coords.x = input.x - m_displayCenter.x;
    coords.y = -input.y + m_displayCenter.y;

    if (true)
    {
        if (m_isPaddlePressed)
        {
            Vector2 pos = m_paddle.m_render.GetPosition();
            switch (input.m_action)
            {
                case InputAction::ActionMove:
                    pos.x = coords.x;
                    if (pos.x - m_paddle.m_touchBoxHalfExtents.x < -m_displaySize.x * 0.5f)
                    {
                        pos.x = (-m_displaySize.x * 0.5f) + m_paddle.m_touchBoxHalfExtents.x;
                    }
                    else if (pos.x + m_paddle.m_touchBoxHalfExtents.x > m_displaySize.x * 0.5f)
                    {
                        pos.x = m_displaySize.x * 0.5f - m_paddle.m_touchBoxHalfExtents.x;
                    }
                    m_paddle.m_render.SetPosition(pos);
                    m_paddle.m_touchBoxCenter.x = pos.x;
                    break;
                case InputAction::ActionUp:
                    if (Utility::IsPointInQuad(coords, m_paddle.m_touchBoxCenter, m_paddle.m_touchBoxHalfExtents))
                    {
                        m_isPaddlePressed = false;
                    }
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
                    if (Utility::IsPointInQuad(coords, m_paddle.m_touchBoxCenter, m_paddle.m_touchBoxHalfExtents))
                    {
                        m_isPaddlePressed = true;
                    }
                    break;
                default:
                    // TODO: reject other actions, only paddle and menu item touches matter at this point
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
    /*
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
     */
}


