#include "Graphics.h"

Graphics::Graphics()
    : m_window(nullptr)
{}

Graphics::~Graphics()
{
    Destroy();
}

bool Graphics::Initialize(ANativeWindow* window)
{
    m_window = window;

    /*
    m_EglDisplay = EGL_NO_DISPLAY;
    m_EglSurface = EGL_NO_SURFACE;
    m_EglContext = EGL_NO_CONTEXT;
    m_EglConfig = 0;

    m_EglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (EGL_FALSE == eglInitialize(m_EglDisplay, 0, 0))
    {
        return false;
    }
    */

    return true;
}

void Graphics::Destroy()
{
    if (m_window != nullptr)
    {
        ANativeWindow_release(m_window);
    }
}
