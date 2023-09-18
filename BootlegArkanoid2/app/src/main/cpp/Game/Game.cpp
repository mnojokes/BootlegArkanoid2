#include "Game.h"
#include "../Renderer.h"
#include "../RenderObject.h"
#include <vector>
#include <game-activity/native_app_glue/android_native_app_glue.h>

Game::Game()
    : m_renderer(nullptr)
    , m_paddle("")
    , m_ball("")
{}

Game::~Game()
{
    // TODO: destruction logic
}

bool Game::Initialize(android_app* app)
{
    if (app == nullptr) { return false; }
    m_renderer = new Renderer(app);
    if (!m_renderer->Initialize())
    {
        return false;
    }

    int32_t i = ANativeWindow_getFormat(app->window);

    m_displaySize.x = static_cast<float>(ANativeWindow_getWidth(app->window));
    m_displaySize.y = static_cast<float>(ANativeWindow_getHeight(app->window));
    m_objectManager.Initialize(m_displaySize);

    m_displayCenterTouch = m_displaySize * 0.5f;
    m_collider.Initialize(m_displayCenterTouch);

    m_paddle = m_objectManager.GetDefaultPaddle();
    m_ball = m_objectManager.GetDefaultBall();

    m_state.SetCurrentState(GameStates::ShowIntro);
    m_isInitialized = m_isStateChanged = true;
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
    if (m_isStateChanged)
    {
        if (m_state.GetCurrentState() == GameStates::Quit)
        {
            // TODO: figure out the way to correctly signal app termination to the top Java layer
            exit(0);
        }
        if (m_currentLevel > m_objectManager.GetNumberOfLevels())
        {
            m_currentLevel = 1;
        }
        if (m_state.GetCurrentState() == GameStates::ShowGameOver)
        {
            m_currentLevelBricks.clear();
            m_paddle = m_objectManager.GetDefaultPaddle();
            m_ball = m_objectManager.GetDefaultBall();
        }
        if (m_state.IsShowingGame())
        {
            if (m_currentLevelBricks.empty())
            {
                m_objectManager.LoadLevelBricks(m_currentLevelBricks, m_currentLevel);
                m_paddle = m_objectManager.GetDefaultPaddle();
                m_ball = m_objectManager.GetDefaultBall();
            }
        }
        m_objectManager.LoadMenuObjects(m_menuItems, m_state.GetCurrentState());
        m_isStateChanged = false;
    }

    // Update game objects when the active state is Playing
    if (m_state.IsShowingGame())
    {
        Vector2 newBallPos = m_collider.ProcessBallMovement(m_ball, m_paddle, m_currentLevelBricks, m_frameCounter.GetDelta());
        m_ball.m_render.SetPosition(newBallPos);
        if (m_ball.m_lost)
        {
            --m_currentLevel;
            m_state.SetCurrentState(GameStates::ShowGameOver);
            m_isStateChanged = true;
        }

        size_t br = 0;
        while (br < m_currentLevelBricks.size())
        {
            if (!m_currentLevelBricks[br].m_isVisible)
            {
                m_currentLevelBricks.erase(m_currentLevelBricks.begin() + br);
                continue;
            }
            ++br;
        }

        if (m_currentLevelBricks.empty())
        { // all bricks destroyed
            ++m_currentLevel;
            if (m_currentLevel <= m_objectManager.GetNumberOfLevels())
            {
                m_state.SetCurrentState(GameStates::ShowPause);
            }
            else
            {
                m_state.SetCurrentState(GameStates::ShowGameOver);
            }
            m_isStateChanged = true;
        }
    }
}

void Game::RenderFrame()
{
    std::vector<const RenderObject*> v;
    if (m_state.IsShowingGame())
    {
        for (const Brick& br : m_currentLevelBricks)
        {
            v.push_back(&br.m_render);
        }
        v.push_back(&m_paddle.m_render);
        v.push_back(&m_ball.m_render);
    }

    for (const MenuItem* mi : m_menuItems)
    {
        v.push_back(&mi->m_render);
    }

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
    Vector2 touched; // coordinates adjusted to match game world's cartesian space
    touched.x = input.x - m_displayCenterTouch.x;
    touched.y = -input.y + m_displayCenterTouch.y;
    // TODO: find a way to get display hardware resolution to correctly calculate coordinates
    //touched.y = -input.y + 2220.0f * 0.5f; // display hardware has different pixel count than client area (2220 on hardware vs 2066 in client area)

    for (const MenuItem* button : m_menuItems)
    {
        if (Collider::IsPointInQuad(touched, button->m_render.GetPosition(), button->m_halfExtents))
        {
            m_isPaddlePressed = false;
            m_state.SetCurrentState(button->m_targetState);
            m_isStateChanged = true;
            return;
        }
    }

    if (m_state.IsShowingGame())
    {
        Vector2 paddlePos;
        switch (input.m_action)
        {
            case InputAction::ActionDown:
                if (Collider::IsPointInQuad(touched, m_paddle.m_touchBoxCenter, m_paddle.m_touchBoxHalfExtents))
                {
                    m_isPaddlePressed = true;
                }
                break;
            case InputAction::ActionUp:
                m_isPaddlePressed = false;
                break;
            case InputAction::ActionMove:
                if (m_isPaddlePressed)
                {
                    paddlePos = m_collider.ProcessPaddleMovementX(m_paddle, touched);
                    m_paddle.m_touchBoxCenter.x = paddlePos.x;
                    m_paddle.m_render.SetPosition(paddlePos);
                }
                break;
            default:
                // TODO: log unknown action
                break;
        }
    }
}
