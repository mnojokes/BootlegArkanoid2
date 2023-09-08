#include "ObjectManager.h"

struct BrickData
{
    int m_row = 0;
    int m_col = 0;
    int m_lives = 0;
};

namespace
{
    const std::vector<BrickData> level0; // empty level
    const std::vector<BrickData> level1 =
            { {0, 0, 1}, { 0, 1, 1}, { 0, 2, 1}, { 0, 3, 1}, { 0, 4, 1}, { 0, 5, 1}, { 0, 6, 1}, { 0, 7, 1}, { 0, 8, 1}, { 0, 9, 1},
              {1, 0, 1}, { 1, 1, 1}, { 1, 2, 1}, { 1, 3, 1}, { 1, 4, 1}, { 1, 5, 1}, { 1, 6, 1}, { 1, 7, 1}, { 1, 8, 1}, { 1, 9, 1},
              {2, 0, 1}, { 2, 1, 1}, { 2, 2, 1}, { 2, 3, 1}, { 2, 4, 1}, { 2, 5, 1}, { 2, 6, 1}, { 2, 7, 1}, { 2, 8, 1}, { 2, 9, 1},
              {3, 0, 1}, { 3, 1, 1}, { 3, 2, 1}, { 3, 3, 1}, { 3, 4, 1}, { 3, 5, 1}, { 3, 6, 1}, { 3, 7, 1}, { 3, 8, 1}, { 3, 9, 1},
              {4, 0, 1}, { 4, 1, 1}, { 4, 2, 1}, { 4, 3, 1}, { 4, 4, 1}, { 4, 5, 1}, { 4, 6, 1}, { 4, 7, 1}, { 4, 8, 1}, { 4, 9, 1},
              {5, 0, 1}, { 5, 1, 1}, { 5, 2, 1}, { 5, 3, 1}, { 5, 4, 1}, { 5, 5, 1}, { 5, 6, 1}, { 5, 7, 1}, { 5, 8, 1}, { 5, 9, 1} };
}

namespace Defaults::Bricks
{
    std::vector<std::vector<BrickData>> layouts = { level0, level1 };
}

ObjectManager::ObjectManager()
    : m_numLevels(static_cast<uint32_t>(Defaults::Bricks::layouts.size()) - 1)
{}

void ObjectManager::SetDefaultBrickPositionTopLeft(Vec2D<float> position)
{
    m_defaultFirstBrickPosition = position;
}

void ObjectManager::SetPaddleDefaults(Vec2D<float> position)
{
    m_defaultPaddlePosition = position;
}

void ObjectManager::SetBallDefaults(Vec2D<float> position, Vec2D<float> velocity)
{
    m_defaultBallPosition = position;
    m_defaultBallVelocity = velocity;
}

void ObjectManager::ResetPaddle(Paddle& paddle) const
{
    paddle.m_position = m_defaultPaddlePosition;
}

void ObjectManager::ResetBall(Ball& ball) const
{
    ball.m_position = m_defaultBallPosition;
    ball.m_velocity = m_defaultBallVelocity;
}

void ObjectManager::ResetBricks(std::vector<Brick>& bricks, uint32_t level) const
{
    bricks.clear();
    if (level > m_numLevels)
    {
        // TODO: log invalid level
        level = 0;
    }
    if (level == 0) { return; }

    size_t numBricks = Defaults::Bricks::layouts[level].size();
    bricks.resize(numBricks);
    Vec2D<float> brickSize = bricks[0].m_halfExtents * 2.0f;
    for (size_t i = 0; i < numBricks; ++i)
    {
        bricks[i].m_lives = Defaults::Bricks::layouts[level][i].m_lives;
        // TODO: adjust position based on row/column of a default brick
        // Consider switching to storing first brick's center instead of top left coordinate
    }
}

uint32_t ObjectManager::GetNumberOfLevels() const
{
    return m_numLevels;
}
