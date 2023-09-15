#pragma once

#include "../Vector.h"
#include <string>
#include "../RenderObject.h"
#include "GameStates.h"

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
    {}

public:
    float m_radius;
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
