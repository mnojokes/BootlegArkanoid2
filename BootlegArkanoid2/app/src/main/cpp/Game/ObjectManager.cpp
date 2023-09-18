#include "ObjectManager.h"

struct BrickData
{
    int m_row = 0;
    int m_col = 0;
    int m_lives = 0;
};

namespace
{
    constexpr float topMarginFromPauseButton = 100.0f;
    constexpr float bottomMarginToPaddle = 200.0f;
    constexpr float defaultBallPositionAbovePaddle = 40.0f;
}

namespace Texture
{
    namespace Brick
    {
        const std::vector<std::string> texture = { "Game/Brick.png" };
    }
    namespace Paddle
    {
        const std::vector<std::string> texture = { "Game/Paddle.png" };
    }
    namespace Ball
    {
        const std::vector<std::string> texture = { "Game/Ball.png" };
    }
    namespace MenuItem
    {
        enum class Menu
        {
            Pause,
            Play,
            Resume,
            Retry,
            Quit,
            Lives,
            Score
        };
        const std::vector<std::string> texture = { "Menu/Pause.png", "Menu/Play.png", "Menu/Resume.png", "Menu/Retry.png", "Menu/Quit.png", "Menu/Lives.png", "Menu/Score.png" };
    }
    namespace Numbers
    {
        const std::vector<std::string> texture = { "Menu/0.png", "Menu/1.png", "Menu/2.png", "Menu/3.png", "Menu/4.png", "Menu/5.png", "Menu/6.png", "Menu/7.png", "Menu/8.png", "Menu/9.png" };
    }
}

namespace Levels
{
    const std::vector<BrickData> level0; // empty level
    const std::vector<BrickData> level1 =
            { { 0, 0, 1 }, { 0, 1, 1 }, { 0, 2, 1 }, { 0, 3, 1 }, { 0, 4, 1 }, { 0, 5, 1 }, { 0, 6, 1 }, { 0, 7, 1 }, { 0, 8, 1 }, { 0, 9, 1 },
              { 1, 0, 1 }, { 1, 1, 1 }, { 1, 2, 1 }, { 1, 3, 1 }, { 1, 4, 1 }, { 1, 5, 1 }, { 1, 6, 1 }, { 1, 7, 1 }, { 1, 8, 1 }, { 1, 9, 1 },
              { 2, 0, 1 }, { 2, 1, 1 }, { 2, 2, 1 }, { 2, 3, 1 }, { 2, 4, 1 }, { 2, 5, 1 }, { 2, 6, 1 }, { 2, 7, 1 }, { 2, 8, 1 }, { 2, 9, 1 },
              { 3, 0, 1 }, { 3, 1, 1 }, { 3, 2, 1 }, { 3, 3, 1 }, { 3, 4, 1 }, { 3, 5, 1 }, { 3, 6, 1 }, { 3, 7, 1 }, { 3, 8, 1 }, { 3, 9, 1 },
              { 4, 0, 1 }, { 4, 1, 1 }, { 4, 2, 1 }, { 4, 3, 1 }, { 4, 4, 1 }, { 4, 5, 1 }, { 4, 6, 1 }, { 4, 7, 1 }, { 4, 8, 1 }, { 4, 9, 1 },
              { 5, 0, 1 }, { 5, 1, 1 }, { 5, 2, 1 }, { 5, 3, 1 }, { 5, 4, 1 }, { 5, 5, 1 }, { 5, 6, 1 }, { 5, 7, 1 }, { 5, 8, 1 }, { 5, 9, 1 } };

    const std::vector<BrickData> level2 =
            {{ 0, 0, 1 }, { 0, 1, 1 }, { 0, 2, 1 }, { 0, 3, 1 }, { 0, 4, 1 }, { 0, 5, 1 }, { 0, 6, 1 }, { 0, 7, 1 }, { 0, 8, 1 }, { 0, 9, 1 },
             { 1, 0, 1 }, { 1, 1, 1 }, { 1, 2, 1 }, { 1, 3, 1 }, { 1, 4, 1 }, { 1, 5, 1 }, { 1, 6, 1 }, { 1, 7, 1 }, { 1, 8, 1 }, { 1, 9, 1 },
             { 2, 0, 1 }, { 2, 1, 1 }, { 2, 2, 1 }, { 2, 3, 1 }, { 2, 4, 1 }, { 2, 5, 1 }, { 2, 6, 1 }, { 2, 7, 1 }, { 2, 8, 1 }, { 2, 9, 1 },
             { 3, 0, 1 }, { 3, 1, 1 }, { 3, 2, 1 }, { 3, 3, 1 }, { 3, 4, 1 }, { 3, 5, 1 }, { 3, 6, 1 }, { 3, 7, 1 }, { 3, 8, 1 }, { 3, 9, 1 },
             { 4, 0, 1 }, { 4, 1, 1 }, { 4, 2, 1 }, { 4, 3, 1 }, { 4, 4, 1 }, { 4, 5, 1 }, { 4, 6, 1 }, { 4, 7, 1 }, { 4, 8, 1 }, { 4, 9, 1 },
             { 5, 0, 1 }, { 5, 1, 1 }, { 5, 2, 1 }, { 5, 3, 1 }, { 5, 4, 1 }, { 5, 5, 1 }, { 5, 6, 1 }, { 5, 7, 1 }, { 5, 8, 1 }, { 5, 9, 1 }};

    const std::vector<BrickData> level3 =
            {{ 0, 0, 1 }, { 0, 1, 1 }, { 0, 2, 1 }, { 0, 3, 1 }, { 0, 4, 1 }, { 0, 5, 1 }, { 0, 6, 1 }, { 0, 7, 1 }, { 0, 8, 1 }, { 0, 9, 1 },
             { 1, 0, 1 }, { 1, 1, 1 }, { 1, 2, 1 }, { 1, 3, 1 }, { 1, 4, 1 }, { 1, 5, 1 }, { 1, 6, 1 }, { 1, 7, 1 }, { 1, 8, 1 }, { 1, 9, 1 },
             { 2, 0, 1 }, { 2, 1, 1 }, { 2, 2, 1 }, { 2, 3, 1 }, { 2, 4, 1 }, { 2, 5, 1 }, { 2, 6, 1 }, { 2, 7, 1 }, { 2, 8, 1 }, { 2, 9, 1 },
             { 3, 0, 1 }, { 3, 1, 1 }, { 3, 2, 1 }, { 3, 3, 1 }, { 3, 4, 1 }, { 3, 5, 1 }, { 3, 6, 1 }, { 3, 7, 1 }, { 3, 8, 1 }, { 3, 9, 1 },
             { 4, 0, 1 }, { 4, 1, 1 }, { 4, 2, 1 }, { 4, 3, 1 }, { 4, 4, 1 }, { 4, 5, 1 }, { 4, 6, 1 }, { 4, 7, 1 }, { 4, 8, 1 }, { 4, 9, 1 },
             { 5, 0, 1 }, { 5, 1, 1 }, { 5, 2, 1 }, { 5, 3, 1 }, { 5, 4, 1 }, { 5, 5, 1 }, { 5, 6, 1 }, { 5, 7, 1 }, { 5, 8, 1 }, { 5, 9, 1 }};
}

namespace Defaults::Bricks
{
    std::vector<std::vector<BrickData>> layouts = { Levels::level0, Levels::level1, Levels::level1, Levels::level1 };
}

ObjectManager::ObjectManager()
    : m_defaultBrick(Texture::Brick::texture[0])
    , m_defaultPaddle(Texture::Paddle::texture[0])
    , m_defaultBall(Texture::Ball::texture[0])
    , m_pauseButton(Texture::MenuItem::texture[0])
    , m_playButton(Texture::MenuItem::texture[1])
    , m_resumeButton(Texture::MenuItem::texture[2])
    , m_retryButton(Texture::MenuItem::texture[3])
    , m_quitButton(Texture::MenuItem::texture[4])
    , m_livesText(Texture::MenuItem::texture[5])
    , m_livesNumber(Texture::MenuItem::texture[6])
{
    m_numLevels = (static_cast<uint32_t>(Defaults::Bricks::layouts.size() - 1));

    m_pauseButton.m_targetState = GameStates::ShowPause;
    m_playButton.m_targetState = m_resumeButton.m_targetState = m_retryButton.m_targetState = GameStates::Playing;
    m_quitButton.m_targetState = GameStates::Quit;

    m_livesNumber.m_isTouchable = false;
    m_livesNumber.m_isTouchable = false;
}

void ObjectManager::Initialize(const Vector2& displayResolution)
{
    float top = displayResolution.y * 0.5f;
    float bottom = -top;
    float right = displayResolution.x * 0.5f;
    float left = -right;

    // Buttons take up 3/4 of the display width, height is 50% of width
    m_playButton.m_halfExtents.x = displayResolution.x * 0.66f * 0.5f;
    m_playButton.m_halfExtents.y = m_playButton.m_halfExtents.x * 0.5f;

    m_resumeButton.m_halfExtents = m_retryButton.m_halfExtents = m_quitButton.m_halfExtents = m_playButton.m_halfExtents;
    m_playButton.m_render.SetScale(m_playButton.m_halfExtents * 2.0f);
    m_resumeButton.m_render.SetScale(m_resumeButton.m_halfExtents * 2.0f);
    m_retryButton.m_render.SetScale(m_retryButton.m_halfExtents * 2.0f);
    m_quitButton.m_render.SetScale(m_quitButton.m_halfExtents * 2.0f);

    float gapBetweenButtons = displayResolution.y * 0.05f;
    m_playButton.m_render.SetPosition({0.0f, m_playButton.m_halfExtents.y + gapBetweenButtons * 0.5f });
    m_resumeButton.m_render.SetPosition(m_playButton.m_render.GetPosition());
    m_retryButton.m_render.SetPosition(m_playButton.m_render.GetPosition());
    m_quitButton.m_render.SetPosition({ 0.0f, -m_quitButton.m_halfExtents.y - gapBetweenButtons * 0.5f });

    // Default brick size - 10 bricks per screen width. Brick height: 50% of width
    m_defaultBrick.m_halfExtents.x = displayResolution.x * 0.1f * 0.5f;
    m_defaultBrick.m_halfExtents.y = m_defaultBrick.m_halfExtents.x * 0.5f;
    m_defaultBrick.m_render.SetScale(m_defaultBrick.m_halfExtents * 2.0f);

    // Pause button - 75% of brick width, square. Positioned in top right corner
    m_pauseButton.m_halfExtents.x = m_defaultBrick.m_halfExtents.x * 0.75f;
    m_pauseButton.m_halfExtents.y = m_pauseButton.m_halfExtents.x;
    m_pauseButton.m_render.SetScale(m_pauseButton.m_halfExtents * 2.0f);
    Vector2 position;
    position.x = right - m_pauseButton.m_halfExtents.x;
    position.y = top - m_pauseButton.m_halfExtents.y;
    m_pauseButton.m_render.SetPosition(position);

    // Default brick position - 10 pixels below pause button's bottom
    position.x = left + m_defaultBrick.m_halfExtents.x;
    position.y = top - (m_defaultBrick.m_halfExtents.y + m_pauseButton.m_halfExtents.y * 2.0f + topMarginFromPauseButton);
    m_defaultBrick.m_render.SetPosition(position);

    // Default paddle - 50% wider than brick. Height: 50% of width
    m_defaultPaddle.m_halfExtents.x = m_defaultBrick.m_halfExtents.x * 1.5f;
    m_defaultPaddle.m_halfExtents.y = m_defaultBrick.m_halfExtents.y;
    position.x = 0.0f;
    position.y = bottom + bottomMarginToPaddle + m_defaultPaddle.m_halfExtents.y;
    m_defaultPaddle.m_render.SetPosition(position);
    m_defaultPaddle.m_render.SetScale(m_defaultPaddle.m_halfExtents * 2.0f);
    m_defaultPaddle.m_render.SetColor(ObjColors::paddle.r, ObjColors::paddle.g, ObjColors::paddle.b, ObjColors::paddle.a);

    // Paddle touch box is 3x higher than paddle object, extends towards the bottom of the display, similar width
    m_defaultPaddle.m_touchBoxHalfExtents.x = m_defaultPaddle.m_halfExtents.x;
    m_defaultPaddle.m_touchBoxHalfExtents.y = m_defaultPaddle.m_halfExtents.y * 3.0f;
    position = m_defaultPaddle.m_render.GetPosition();
    m_defaultPaddle.m_touchBoxCenter.x = position.x;
    m_defaultPaddle.m_touchBoxCenter.y = position.y - m_defaultPaddle.m_halfExtents.y * 2.0f;

    // Default ball - 33% of brick width, positioned 10 pixels above paddle
    m_defaultBall.m_radius = (m_defaultBrick.m_halfExtents.x * 2.0f) * 0.33f;
    position = m_defaultPaddle.m_render.GetPosition();
    position.y += (m_defaultPaddle.m_halfExtents.y + m_defaultBall.m_radius + defaultBallPositionAbovePaddle);
    m_defaultBall.m_render.SetPosition(position);
    m_defaultBall.m_render.SetScale( {m_defaultBall.m_radius * 2.0f, m_defaultBall.m_radius * 2.0f} );

    // Ball starts at 45deg upward right trajectory
    m_defaultBall.m_velocity.x = displayResolution.x * 0.01f;
    m_defaultBall.m_velocity.y = m_defaultBall.m_velocity.x;
}

void ObjectManager::LoadMenuObjects(std::vector<const MenuItem*>& menuItems, GameStates state)
{
    menuItems.clear();
    switch(state)
    {
        case GameStates::NONE:
            // TODO: log invalid state
            return;
        case GameStates::Playing:
            menuItems.push_back(&m_pauseButton);
            // TODO: add lives and score
            break;
        case GameStates::ShowIntro:
            menuItems.push_back(&m_playButton);
            menuItems.push_back(&m_quitButton);
            break;
        case GameStates::ShowPause:
            menuItems.push_back(&m_resumeButton);
            menuItems.push_back(&m_quitButton);
            break;
        case GameStates::ShowGameOver:
            menuItems.push_back(&m_retryButton);
            menuItems.push_back(&m_quitButton);
            break;
        default:
            // TODO: log unknown state
            break;
    }
}

void ObjectManager::LoadLevelBricks(std::vector<Brick>& bricks, uint32_t level)
{
    bricks.clear();
    if (level > m_numLevels)
    {
        // TODO: log invalid level
        level = 0;
    }
    if (level == 0)
    {
        return;
    }

    size_t numBricks = Defaults::Bricks::layouts[level].size();
    for (size_t i = 0; i < numBricks; ++i)
    {
        Brick b = m_defaultBrick;
        Vector2 position = m_defaultBrick.m_render.GetPosition();
        position.x += m_defaultBrick.m_halfExtents.x * 2.0f * static_cast<float>(Defaults::Bricks::layouts[level][i].m_col);
        position.y -= m_defaultBrick.m_halfExtents.y * 2.0f * static_cast<float>(Defaults::Bricks::layouts[level][i].m_row);
        b.m_render.SetPosition(position);
        b.m_lives = Defaults::Bricks::layouts[level][i].m_lives;
        b.SetColorOnLives();
        bricks.push_back(b);
    }
}

const Paddle& ObjectManager::GetDefaultPaddle() const
{
    return m_defaultPaddle;
}

const Ball& ObjectManager::GetDefaultBall() const
{
    return m_defaultBall;
}

uint32_t ObjectManager::GetNumberOfLevels() const
{
    return m_numLevels;
}
