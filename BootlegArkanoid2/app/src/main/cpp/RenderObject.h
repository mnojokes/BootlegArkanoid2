#ifndef BOOTLEG_ARKANOID_2_RENDEROBJECT_H
#define BOOTLEG_ARKANOID_2_RENDEROBJECT_H

#include <string>
#include "Vector.h"

class RenderObject
{
public:
    RenderObject(const std::string& texturePath)
            : m_texturePath(texturePath)
    {}

    void SetPosition(const Vector2& position) { m_position = position; }
    void SetScale(const Vector2& scale) { m_scale = scale; }

    const std::string& GetTexturePath(void) const { return m_texturePath; }
    const Vector2& GetPosition(void) const { return m_position; }
    const Vector2& GetScale(void) const { return m_scale; }

private:
    std::string m_texturePath;
    Vector2 m_position;
    Vector2 m_scale;
};

#endif //BOOTLEG_ARKANOID_2_RENDEROBJECT_H
