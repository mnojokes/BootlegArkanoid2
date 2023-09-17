#include "Renderer.h"

#include <vector>
#include "AndroidOut.h"
#include "Utility.h"
#include <game-activity/native_app_glue/android_native_app_glue.h>

Renderer::Renderer(android_app *app)
        : m_app(app)
        , m_display(EGL_NO_DISPLAY)
        , m_surface(EGL_NO_SURFACE)
        , m_context(EGL_NO_CONTEXT)
        , m_width(-1)
        , m_height(-1)
        , m_textureManager(m_app->activity->assetManager)
        , m_rectVertices{
                {Vector3{-0.5f, 0.5f, 0}, Vector2{0, 0}},
                {Vector3{0.5f, 0.5f, 0}, Vector2{1, 0}},
                {Vector3{0.5f, -0.5f, 0}, Vector2{1, 1}},
                {Vector3{-0.5f, 0.5f, 0}, Vector2{0, 0}},
                {Vector3{0.5f, -0.5f, 0}, Vector2{1, 1}},
                {Vector3{-0.5f, -0.5f, 0}, Vector2{0, 1}}}
{}

Renderer::~Renderer()
{
    if (m_display != EGL_NO_DISPLAY)
    {
        eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (m_context != EGL_NO_CONTEXT)
        {
            eglDestroyContext(m_display, m_context);
            m_context = EGL_NO_CONTEXT;
        }
        if (m_surface != EGL_NO_SURFACE)
        {
            eglDestroySurface(m_display, m_surface);
            m_surface = EGL_NO_SURFACE;
        }
        eglTerminate(m_display);
        m_display = EGL_NO_DISPLAY;
    }
}

bool Renderer::Initialize()
{
    constexpr EGLint openGLAttributes[] =
            {
                    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
                    EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                    EGL_BLUE_SIZE, 8,
                    EGL_GREEN_SIZE, 8,
                    EGL_RED_SIZE, 8,
                    EGL_DEPTH_SIZE, 24,
                    EGL_NONE
            };

    m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    auto result = eglInitialize(m_display, nullptr, nullptr);
    if (!result)
    {
        return false;
    }

    EGLint numConfigs;
    eglChooseConfig(m_display, openGLAttributes, nullptr, 0, &numConfigs);

    std::unique_ptr<EGLConfig[]> supportedConfigs(new EGLConfig[numConfigs]);
    eglChooseConfig(m_display, openGLAttributes, supportedConfigs.get(), numConfigs, &numConfigs);

    // Find a config we like.
    // Could likely just grab the first if we don't care about anything else in the config.
    // Otherwise hook in your own heuristic
    auto config = *std::find_if(
            supportedConfigs.get(),
            supportedConfigs.get() + numConfigs,
            [this](const EGLConfig &config)
            {
                EGLint red, green, blue, depth;
                if (eglGetConfigAttrib(m_display, config, EGL_RED_SIZE, &red)
                    && eglGetConfigAttrib(m_display, config, EGL_GREEN_SIZE, &green)
                    && eglGetConfigAttrib(m_display, config, EGL_BLUE_SIZE, &blue)
                    && eglGetConfigAttrib(m_display, config, EGL_DEPTH_SIZE, &depth)) {

                    aout << "Found config with " << red << ", " << green << ", " << blue << ", "
                         << depth << std::endl;
                    return red == 8 && green == 8 && blue == 8 && depth == 24;
                }
                return false;
            });

    aout << "Found " << numConfigs << " configs" << std::endl;
    aout << "Chose " << config << std::endl;

    EGLint format;
    eglGetConfigAttrib(m_display, config, EGL_NATIVE_VISUAL_ID, &format);
    m_surface = eglCreateWindowSurface(m_display, config, m_app->window, nullptr);

    // Create a GLES 3 context
    EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
    EGLContext context = eglCreateContext(m_display, config, nullptr, contextAttribs);

    // get some window metrics
    result = eglMakeCurrent(m_display, m_surface, m_surface, context);
    if (!result)
    {
        return false;
    }

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    if (vertexShader != 0)
    {
        const std::string vertexShaderCode = R"vertex(#version 300 es
            in vec3 inPosition;
            in vec2 inUV;

            out vec2 fragUV;

            uniform mat4 uProjection;
            uniform mat4 uTransform;

            void main()
            {
                fragUV = inUV;
                mat4 worldProjection = uProjection * uTransform;
                gl_Position = worldProjection * vec4(inPosition, 1.0);
            }
        )vertex";

        GLint vertexShaderSize = static_cast<GLint>(vertexShaderCode.size());
        const GLchar* vertexShaderData = vertexShaderCode.c_str();
        glShaderSource(vertexShader, 1, &vertexShaderData, &vertexShaderSize);
        glCompileShader(vertexShader);
    }
    else
    {
        return false;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (fragmentShader != 0)
    {
        const std::string fragmentShaderCode = R"fragment(#version 300 es
            precision mediump float;

            in vec2 fragUV;

            uniform sampler2D uTexture;

            uniform vec4 uColor;

            out vec4 outColor;

            void main()
            {
                outColor = texture(uTexture, fragUV);
                outColor *= uColor;
            }
        )fragment";

        GLint fragmentShaderSize = static_cast<GLint>(fragmentShaderCode.size());
        const GLchar* fragmentShaderData = fragmentShaderCode.c_str();
        glShaderSource(fragmentShader, 1, &fragmentShaderData, &fragmentShaderSize);
        glCompileShader(fragmentShader);
    }
    else
    {
        return false;
    }

    m_shaderProgram = glCreateProgram();
    if (m_shaderProgram != 0)
    {
        glAttachShader(m_shaderProgram, vertexShader);
        glAttachShader(m_shaderProgram, fragmentShader);
        glLinkProgram(m_shaderProgram);

        m_vertexShaderAttributePosition = glGetAttribLocation(m_shaderProgram, "inPosition");
        m_vertexShaderAttributeUV = glGetAttribLocation(m_shaderProgram, "inUV");
        m_vertexShaderAttributeProjection = glGetUniformLocation(m_shaderProgram, "uProjection");
        m_vertexShaderAttributeTransform = glGetUniformLocation(m_shaderProgram, "uTransform");
        m_fragmentShaderAttributeColor = glGetUniformLocation(m_shaderProgram, "uColor");
    }
    else
    {
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(m_shaderProgram);

    return true;
}

void Renderer::Render(const std::vector<const RenderObject*> m_renderObjects)
{
    // Check to see if the surface has changed size. This is _necessary_ to do every frame when
    // using immersive mode as you'll get no other notification that your renderable area has
    // changed.
    UpdateRenderArea();

    glClear(GL_COLOR_BUFFER_BIT);

    if (!m_renderObjects.empty())
    {
        glVertexAttribPointer(
                m_vertexShaderAttributePosition,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                m_rectVertices
        );
        glEnableVertexAttribArray(m_vertexShaderAttributePosition);

        glVertexAttribPointer(
                m_vertexShaderAttributeUV,
                2,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                ((uint8_t *) m_rectVertices) + sizeof(Vector3)
        );
        glEnableVertexAttribArray(m_vertexShaderAttributeUV);

        for (const RenderObject* renderObject: m_renderObjects)
        {
            const std::string& texturePath = renderObject->GetTexturePath();
            const Texture* texture = m_textureManager.GetTexture(texturePath);
            if (texture == nullptr)
            {
                bool textureCreated = m_textureManager.CreateTexture(texturePath);
                assert(textureCreated);

                texture = m_textureManager.GetTexture(texturePath);
            }

            float transform[16];

            Utility::buildTransformMatrix(transform, renderObject->GetPosition(), renderObject->GetScale());

            glUniformMatrix4fv(m_vertexShaderAttributeTransform, 1, false, transform);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture->GetID());
            const Color& col = renderObject->GetColor();
            glUniform4f(m_fragmentShaderAttributeColor, col.r, col.g, col.b, col.a);

            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        glDisableVertexAttribArray(m_vertexShaderAttributeUV);
        glDisableVertexAttribArray(m_vertexShaderAttributePosition);

    }

    eglSwapBuffers(m_display, m_surface);
}

void Renderer::UpdateRenderArea()
{
    EGLint width;
    eglQuerySurface(m_display, m_surface, EGL_WIDTH, &width);

    EGLint height;
    eglQuerySurface(m_display, m_surface, EGL_HEIGHT, &height);

    if (width != m_width || height != m_height)
    {
        m_width = width;
        m_height = height;
        glViewport(0, 0, width, height);

        float projectionMatrix[16] = {0};

        Utility::buildOrthographicMatrix(projectionMatrix, static_cast<float>(m_width), static_cast<float>(m_height));

        glUniformMatrix4fv(m_vertexShaderAttributeProjection, 1, false, projectionMatrix);
    }
}
