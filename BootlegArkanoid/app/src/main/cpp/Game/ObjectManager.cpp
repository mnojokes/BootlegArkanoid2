#include "ObjectManager.h"

struct BrickData
{
    int m_row = 0;
    int m_col = 0;
    int m_lives = 0;
};

namespace
{
    constexpr float topMarginFromPauseButton = 5.0f;
    constexpr float bottomMarginToPaddle = 200.0f;
    constexpr float defaultBallPositionAbovePaddle = 10.0f;
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

ObjectManager::ObjectManager(const Vec2D<float>& displayResolution)
: m_displayResolution(displayResolution)
, m_numLevels(static_cast<uint32_t>(Defaults::Bricks::layouts.size() - 1))
{
    // Default brick size - 10 bricks per screen width. Brick height: 50% of width
    m_defaultBrick.m_halfExtents.x = m_displayResolution.x * 0.1f * 0.5f;
    m_defaultBrick.m_halfExtents.y = m_defaultBrick.m_halfExtents.x * 0.5f;

    // Pause button - 75% of brick width, square. Positioned in top right corner
    m_defaultPauseButton.m_halfExtents.x = m_defaultBrick.m_halfExtents.x * 0.75f;
    m_defaultPauseButton.m_halfExtents.y = m_defaultPauseButton.m_halfExtents.x;
    m_defaultPauseButton.m_position.x = m_displayResolution.x - m_defaultPauseButton.m_halfExtents.x;
    m_defaultPauseButton.m_position.y = m_defaultPauseButton.m_halfExtents.y;

    // Default brick position - 5 pixels below pause button's bottom
    m_defaultBrick.m_position.x = m_defaultBrick.m_halfExtents.x;
    m_defaultBrick.m_position.y = m_defaultBrick.m_halfExtents.y + m_defaultPauseButton.m_halfExtents.y * 2.0f + topMarginFromPauseButton;

    // Default paddle - 25% wider than brick. Height: 50% of width
    m_defaultPaddle.m_halfExtents.x = m_defaultBrick.m_halfExtents.x * 1.25f;
    m_defaultPaddle.m_halfExtents.y = m_defaultPaddle.m_halfExtents.x * 0.5f;
    m_defaultPaddle.m_position.x = m_displayResolution.x * 0.5f;
    m_defaultPaddle.m_position.y = m_displayResolution.y - bottomMarginToPaddle - m_defaultPaddle.m_halfExtents.y;
    // Paddle touch box is 3x higher than paddle object, extends towards the bottom of the display, similar width
    m_defaultPaddle.m_touchBoxHalfExtents.x = m_defaultPaddle.m_halfExtents.x;
    m_defaultPaddle.m_touchBoxHalfExtents.y = m_defaultPaddle.m_halfExtents.y * 3.0f;
    m_defaultPaddle.m_touchBoxCenter.x = m_defaultPaddle.m_position.x;
    m_defaultPaddle.m_touchBoxCenter.y = m_defaultPaddle.m_position.y + m_defaultPaddle.m_halfExtents.y * 2.0f;

    // Default ball - 33% of brick width, positioned 5 pixels above paddle
    m_defaultBall.m_radius = (m_defaultBrick.m_halfExtents.x * 2.0f) * 0.33f;
    m_defaultBall.m_position.x = m_defaultPaddle.m_position.x;
    m_defaultBall.m_position.y = m_defaultPaddle.m_position.y - defaultBallPositionAbovePaddle;
    // Ball starts at 45deg upward right trajectory
    m_defaultBall.m_velocity.x = m_displayResolution.x * 0.5f;
    m_defaultBall.m_velocity.y = m_defaultBall.m_velocity.x;
}

const MenuItem& ObjectManager::GetDefaultPauseButton() const
{
    return m_defaultPauseButton;
}

const Paddle& ObjectManager::GetDefaultPaddle() const
{
    return m_defaultPaddle;
}

const Ball& ObjectManager::GetDefaultBall() const
{
    return m_defaultBall;
}

void ObjectManager::GetDefaults(std::vector<GameObject>& bricks, uint32_t level) const
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
        b.m_position.x = m_defaultBrick.m_position.x + m_defaultBrick.m_halfExtents.x * 2.0f * static_cast<float>(Defaults::Bricks::layouts[level][i].m_col);
        b.m_position.y = m_defaultBrick.m_position.y + m_defaultBrick.m_halfExtents.y * 2.0f * static_cast<float>(Defaults::Bricks::layouts[level][i].m_row);
        b.m_lives = Defaults::Bricks::layouts[level][i].m_lives;
        // TODO: assign material/texture based on lives
        bricks.push_back(b);
    }
}

void ObjectManager::GetDefaults(std::vector<GameObject>& menuItems, MenuType menu) const
{
    menuItems.clear();
    // TODO
}

const Vec2D<float>& ObjectManager::GetDisplayResolution() const
{
    return m_displayResolution;
}

uint32_t ObjectManager::GetNumberOfLevels() const
{
    return m_numLevels;
}
