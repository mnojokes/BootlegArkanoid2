#pragma once

#include "../Tools/Vector2D.h"

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

    Vec2D<float> m_position;
    Vec2D<float> m_velocity;

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
    Vec2D<float> m_halfExtents;
    int m_lives = 0;
};

class Paddle : public GameObject
{
public:
    Paddle(void)
    : GameObject(ObjectType::Paddle, ColliderShape::AABB, true)
    {}

public:
    Vec2D<float> m_halfExtents;
    Vec2D<float> m_touchBoxCenter;
    Vec2D<float> m_touchBoxHalfExtents;
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
    Vec2D<float> m_halfExtents;
};
