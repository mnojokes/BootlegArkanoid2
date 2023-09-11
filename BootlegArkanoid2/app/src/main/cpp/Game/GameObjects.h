#pragma once

#include "../Vector.h"
#include <string>

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

protected:
    explicit GameObject(ObjectType type, ColliderShape colliderShape, bool touchable = false)
    : m_type(type)
    , m_colliderShape(colliderShape)
    , m_isTouchable(touchable)
    , m_isVisible(true)
    {}

public:
    bool m_isVisible;

    Vector2 m_position;
    Vector2 m_velocity;

    const ColliderShape m_colliderShape;
    const bool m_isTouchable;
private:
    ObjectType m_type;
};

class Brick : public GameObject
{
public:
    Brick(void)
    : GameObject(ObjectType::Brick, ColliderShape::AABB)
    {}

public:
    Vector2 m_halfExtents;
    int m_lives = 0;
};

class Paddle : public GameObject
{
public:
    Paddle(void)
    : GameObject(ObjectType::Paddle, ColliderShape::AABB, true)
    {}

public:
    Vector2 m_halfExtents;
    Vector2 m_touchBoxCenter;
    Vector2 m_touchBoxHalfExtents;
};

class Ball : public GameObject
{
public:
    Ball(void)
    : GameObject(ObjectType::Ball, ColliderShape::Circle)
    {}

public:
    float m_radius;
};

class MenuItem : public GameObject
{
public:
    MenuItem(void)
    : GameObject(ObjectType::MenuItem, ColliderShape::None, true)
    {}

public:
    Vector2 m_halfExtents;
};
