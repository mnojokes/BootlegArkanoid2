#pragma once

#include "GameObjects.h"
#include <vector>

enum class MenuType
{
    Intro,
    Pause,
    LevelCompleted,
    GameOver
};

class ObjectManager
{
public:
    explicit ObjectManager(const Vector2& displayResolution);

    // Get default object values (for setting/resetting levels)
    const MenuItem& GetDefaultPauseButton(void) const;
    const Paddle& GetDefaultPaddle(void) const;
    const Ball& GetDefaultBall(void) const;
    void GetDefaults(std::vector<GameObject>& bricks, uint32_t level) const;
    void GetDefaults(std::vector<GameObject>& menuItems, MenuType menu) const;

    const Vector2& GetDisplayResolution(void) const;
    uint32_t GetNumberOfLevels(void) const;

private:
    Vector2 m_displayResolution;
    uint32_t m_numLevels;

    // Object defaults
    MenuItem m_defaultPauseButton;
    Brick m_defaultBrick;
    Paddle m_defaultPaddle;
    Ball m_defaultBall;
};
