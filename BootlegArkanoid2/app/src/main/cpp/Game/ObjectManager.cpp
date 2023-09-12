#include "ObjectManager.h"

struct BrickData
{
    int m_row = 0;
    int m_col = 0;
    int m_lives = 0;
};

namespace
{
    constexpr float topMarginFromPauseButton = 10.0f;
    constexpr float bottomMarginToPaddle = 200.0f;
    constexpr float defaultBallPositionAbovePaddle = 10.0f;
}

namespace Texture
{
    namespace Brick
    {
        const std::vector<std::string> texture = { "Invalid.png", "Brick1.png", "Brick2.png", "Brick3.png " };
    }
    namespace Paddle
    {
        const std::vector<std::string> texture = { "Paddle.png" };
    }
    namespace Ball
    {
        const std::vector<std::string> texture = { "Ball.png" };
    }
    namespace MenuItem
    {
        const std::vector<std::string> texture = { "Start.png", "Resume.png", "Retry.png.", "Quit.png", "Lives.png", "Score.png" };
    }
    namespace Numbers
    {
        const std::vector<std::string> texture = { "0.png", "1.png", "2.png", "3.png", "4.png", "5.png", "6.png", "7.png", "8.png", "9.png" };
    }
}

namespace Menus
{
    const std::vector<std::vector<MenuItem>> menuIntro;
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
}

namespace Defaults::Bricks
{
    std::vector<std::vector<BrickData>> layouts = { Levels::level0, Levels::level1 };
}

ObjectManager::ObjectManager(void)
    : m_defaultBrick(Texture::Brick::texture[1])
    , m_defaultPaddle(Texture::Paddle::texture[0])
    , m_defaultBall(Texture::Ball::texture[0])
    , m_pauseButton(Texture::MenuItem::texture[0])
    ,m_playButton(Texture::MenuItem::texture[0])
    ,m_retryButton(Texture::MenuItem::texture[0])
    ,m_resumeButton(Texture::MenuItem::texture[0])
    ,m_quitButton(Texture::MenuItem::texture[0])
    ,m_livesText(Texture::MenuItem::texture[0])
    ,m_livesNumber(Texture::MenuItem::texture[0])
{}

void ObjectManager::Initialize(const Vector2& displayResolution)
{
    float top = displayResolution.y * 0.5f;
    float bottom = -top;
    float right = displayResolution.x * 0.5f;
    float left = -right;

    m_numLevels = (static_cast<uint32_t>(Defaults::Bricks::layouts.size() - 1));

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
    m_defaultBall.m_velocity.x = displayResolution.x * 0.005f;
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
        // TODO: assign material/texture based on lives
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

const std::string& ObjectManager::GetTexture(const Brick& obj) const
{
    return Texture::Brick::texture[obj.m_lives];
}
const std::string& ObjectManager::GetTexture(const Paddle& obj) const
{
    return Texture::Paddle::texture[0];
}
const std::string& ObjectManager::GetTexture(const Ball& obj) const
{
    return Texture::Ball::texture[0];
}
const std::string& ObjectManager::GetTexture(const MenuItem& obj) const
{
    return Texture::MenuItem::texture[0];
}

uint32_t ObjectManager::GetNumberOfLevels() const
{
    return m_numLevels;
}
