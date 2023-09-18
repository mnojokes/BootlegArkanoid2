#pragma once

#include "../Vector.h"
#include <string>
#include "../RenderObject.h"
#include "GameStates.h"

constexpr int maxNumBallCollisions = 10;
constexpr float velocityIncrease = 1.1f;

namespace ObjColors
{
    const Color brick1 = { 0.52f, 0.87f, 0.01f, 1.0f }; // lawn green
    const Color brick2 = { 1.0f, 0.75f, 0.0f, 1.0f }; // light amber
    const Color brick3 = { 0.89f, 0.15f, 0.21f, 1.0f }; // crimson red

    const Color paddle = { 0.0f, 0.28f, 0.73f, 1.0f }; // navy blue

    const Color wall = { 1.0f, 0.49f, 0.0f, 1.0f }; // amber
}

enum class ObjectType
{
    Brick,
    Paddle,
    Ball,
    MenuItem
};

enum class ColliderShape
{
    None, // does not collide
    AABB,
    Circle
};

class GameObject
{
public:
    ObjectType GetType(void) const { return m_type; }
    GameObject(std::string texture, ObjectType type, ColliderShape colliderShape, bool touchable = false)
        : m_render(texture)
        , m_type(type)
        , m_colliderShape(colliderShape)
        , m_isTouchable(touchable)
        , m_isVisible(true)
    {}

public:
    RenderObject m_render;
    bool m_isVisible;

    Vector2 m_velocity;

    ColliderShape m_colliderShape;
    bool m_isTouchable;
private:
    ObjectType m_type;
};

class Brick : public GameObject
{
public:
    Brick(std::string texture)
    : GameObject(texture, ObjectType::Brick, ColliderShape::AABB)
    {}

    void SetColorOnLives(void)
    {
        Color newColor;
        switch (m_lives)
        {
            case 3:
                newColor = Color(ObjColors::brick3);
                break;
            case 2:
                newColor = Color(ObjColors::brick2);
                break;
            case 1:
                newColor = Color(ObjColors::brick1);
                break;
            default:
                newColor = Color({ 1, 1, 1, 1 });
                break;
        }
        m_render.SetColor(newColor.r, newColor.g, newColor.b, newColor.a);
    }

    void SignalCollision(void)
    {
        --m_lives;
        if (m_lives <= 0)
        {
            m_isVisible = false;
        }
        else
        {
            SetColorOnLives();
        }
    }

public:
    Vector2 m_halfExtents;
    int m_lives = 0;
};

class Paddle : public GameObject
{
public:
    Paddle(std::string texture)
    : GameObject(texture, ObjectType::Paddle, ColliderShape::AABB, true)
    {}

public:
    Vector2 m_halfExtents;
    Vector2 m_touchBoxCenter;
    Vector2 m_touchBoxHalfExtents;
};

class Ball : public GameObject
{
public:
    Ball(std::string texture)
    : GameObject(texture, ObjectType::Ball, ColliderShape::Circle)
    , m_radius(1.0f)
    , m_numCollisions(0)
    , m_lost(false)
    {}

    void SignalCollision(void)
    {
        ++m_numCollisions;
        if (m_numCollisions == maxNumBallCollisions)
        {
            m_velocity.x *= velocityIncrease;
            m_velocity.y *= velocityIncrease;
            m_numCollisions = 0;
        }
    }

    void SignalBottomWallTouch(void)
    {
        m_lost = true;
    }

public:
    float m_radius;
    int m_numCollisions;
    bool m_lost;
};

class MenuItem : public GameObject
{
public:
    MenuItem(std::string texture)
    : GameObject(texture, ObjectType::MenuItem, ColliderShape::None, true)
    , m_targetState(GameStates::NONE)
    {}

public:
    Vector2 m_halfExtents;
    GameStates m_targetState; // state that the menu item is supposed to invoke
};
