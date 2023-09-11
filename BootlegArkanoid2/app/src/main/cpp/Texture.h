#ifndef BOOTLEG_ARKANOID_2_TEXTURE_H
#define BOOTLEG_ARKANOID_2_TEXTURE_H

#include <GLES3/gl3.h>

class Texture
{
public:
    Texture(int32_t width, int32_t height, int32_t stride, GLuint ID)
            : m_width(width)
            , m_height(height)
            , m_stride(stride)
            , m_ID(ID)
    {}

    int32_t GetWidth(void) const { return m_width; }
    int32_t GetHeight(void) const { return m_height; }
    int32_t GetStride(void) const { return m_stride; }
    GLuint GetID(void) const { return m_ID; }

private:
    int32_t m_width;
    int32_t m_height;
    int32_t m_stride;
    GLuint m_ID;
};

#endif //BOOTLEG_ARKANOID_2_TEXTURE_H
