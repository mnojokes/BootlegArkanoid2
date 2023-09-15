#ifndef ANDROIDGLINVESTIGATIONS_RENDERER_H
#define ANDROIDGLINVESTIGATIONS_RENDERER_H

#include <EGL/egl.h>
#include "TextureManager.h"
#include "RenderObject.h"
#include "Vertex.h"

class Renderer
{
public:
    Renderer(struct android_app *app);
    ~Renderer();

    bool Initialize(void);
    void Render(const std::vector<const RenderObject*> m_renderObjects);

    // App ptr is stored in renderer for it always uses it. To avoid duplication, other systems can get the app ptr from here.
    android_app* GetAppPtr(void) { return m_app; }

private:
    /*!
     * @brief we have to check every frame to see if the framebuffer has changed in size. If it has,
     * update the viewport accordingly
     */
    void UpdateRenderArea();

    android_app* m_app;
    EGLDisplay m_display;
    EGLSurface m_surface;
    EGLContext m_context;
    EGLint m_width;
    EGLint m_height;

    TextureManager m_textureManager;
    Vertex m_rectVertices[6];
    GLint m_vertexShaderAttributePosition;
    GLint m_vertexShaderAttributeUV;
    GLint m_vertexShaderAttributeProjection;
    GLint m_vertexShaderAttributeTransform;
    GLint m_shaderProgram;
};

#endif //ANDROIDGLINVESTIGATIONS_RENDERER_H