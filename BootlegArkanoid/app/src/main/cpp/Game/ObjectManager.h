#pragma once

#include "GameObjects.h"
#include <vector>

class ObjectManager
{
public:
    ObjectManager(void);

    void SetDefaultBrickPositionTopLeft(Vec2D<float> position);
    void SetPaddleDefaults(Vec2D<float> position);
    void SetBallDefaults(Vec2D<float> position, Vec2D<float> velocity);
    void ResetPaddle(Paddle& paddle) const;
    void ResetBall(Ball& ball) const;
    void ResetBricks(std::vector<Brick>& bricks, uint32_t level) const;

    uint32_t GetNumberOfLevels(void) const;

private:
    uint32_t m_numLevels;

    Vec2D<float> m_defaultFirstBrickPosition;
    Vec2D<float> m_defaultPaddlePosition;
    Vec2D<float> m_defaultBallPosition;
    Vec2D<float> m_defaultBallVelocity;
};
