#pragma once
#include <android/native_window.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <EGL/egl.h>

class Graphics
{
public:
    Graphics(void);
    ~Graphics(void);

    bool Initialize(ANativeWindow* window);
    void Destroy(void);

    // TODO: handle window created/destroyed messages with callbacks

private:
    ANativeWindow* m_window;

    /*
    EGLDisplay m_EglDisplay;
    EGLSurface m_EglSurface;
    EGLContext m_EglContext;
    EGLConfig m_EglConfig;
    */
};
