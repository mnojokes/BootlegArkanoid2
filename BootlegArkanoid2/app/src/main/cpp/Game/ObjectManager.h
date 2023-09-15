#pragma once

#include "GameObjects.h"
#include <vector>
#include "GameStates.h"

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
    ObjectManager(void);
    void Initialize(const Vector2& screenResolution);

    // Get default object values (for setting/resetting levels)
    const Paddle& GetDefaultPaddle(void) const;
    const Ball& GetDefaultBall(void) const;

    void LoadMenuObjects(std::vector<const MenuItem*>& objects, GameStates state);
    void LoadLevelBricks(std::vector<Brick>& bricks, uint32_t level);

    uint32_t GetNumberOfLevels(void) const;

private:
    uint32_t m_numLevels{};

    // Default in-game objects
    Brick m_defaultBrick;
    Paddle m_defaultPaddle;
    Ball m_defaultBall;

    // Default menu items
    MenuItem m_pauseButton;
    MenuItem m_playButton;
    MenuItem m_retryButton;
    MenuItem m_resumeButton;
    MenuItem m_quitButton;

    MenuItem m_livesText;
    MenuItem m_livesNumber;
};
