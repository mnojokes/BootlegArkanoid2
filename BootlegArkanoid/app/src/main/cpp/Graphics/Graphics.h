#pragma once
#include <android/native_window.h>
#include <EGL/egl.h>

class Graphics
{
public:
    bool Initialize(ANativeWindow* window);

private:
    ANativeWindow* m_window;

    EGLDisplay m_EglDisplay;
    EGLSurface m_EglSurface;
    EGLContext m_EglContext;
    EGLConfig m_EglConfig;
};
